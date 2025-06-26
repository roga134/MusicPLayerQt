#ifndef MUSICPLAYER_COMMANDS_H
#define MUSICPLAYER_COMMANDS_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QStringListModel>
#include <QMediaMetaData>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QInputDialog>
#include <QDataStream>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <memory>
#include <random>
#include <QDebug>
#include <QDir>
#include <QFileSystemModel>
#include <QStack>
#include <QTimer>
#include <fstream>
#include <QRandomGenerator>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "VisualizerWidget.h"


enum RepeatMode
{
    NoRepeat,RepreatOne ,RepeatAll
};

// command pattern
class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() =0 ;
    virtual void undo() =0 ;
    virtual QString description() const =0 ;
};


class PlayCommand : public Command
{
public:
    PlayCommand(QMediaPlayer* player , std::list<QUrl>::iterator track);

    void execute() override;

    void undo() override;

    QString description() const override;

private:
    QMediaPlayer* player;
    std::list<QUrl>::iterator track;
    std::list<QUrl>::iterator lasttrack;
};


class PauseCommand : public Command
{
public:
    PauseCommand(QMediaPlayer* player);

    void execute() override ;


    void undo() override ;

    QString description() const override ;

private:
    QMediaPlayer* player;

};

class AddTrackCommand : public Command
{
public:

    AddTrackCommand(std::list<QUrl>& playlist, QStandardItemModel* model, const QUrl& track);
    std::list<QUrl>::iterator executeWithResult();
    void execute() override {
        executeWithResult();
    }
    void undo() override;
    QString description() const override;

private:

    std::list<QUrl>& playlist;
    QStandardItemModel* model;
    QUrl track;
};


class RemoveTrackCommand : public Command {
public:
    RemoveTrackCommand(std::list<QUrl>& playlist, QStandardItemModel* model, std::list<QUrl>::iterator track);

    void execute() override ;

    void undo() override ;

    QString description() const override ;

private:
    std::list<QUrl>& playlist;
    QStandardItemModel* model;
    std::list<QUrl>::iterator track;
    int pos;
};


class NextTrackCommand : public Command {
public:
    NextTrackCommand(QMediaPlayer* player, std::list<QUrl>& playlist, std::list<QUrl>::iterator& currentTrack,
                     QStandardItemModel* model, RepeatMode repeatMode, bool shuffle,
                     std::vector<int>& shuffledIndices, int& shuffleIndex);

    void execute() override;
    void undo() override;
    QString description() const override;

private:
    QMediaPlayer* player;
    std::list<QUrl>& playlist;
    std::list<QUrl>::iterator& currentTrack;
    std::list<QUrl>::iterator originalTrack;
    QStandardItemModel* model;
    RepeatMode repeatMode;
    bool shuffle;
    std::vector<int>& shuffledIndices;
    int& shuffleIndex;
};


class PreviousTrackCommand : public Command {
public:
    PreviousTrackCommand(QMediaPlayer* player, std::list<QUrl>& playlist, std::list<QUrl>::iterator& currentTrack,
                         QStandardItemModel* model, RepeatMode repeatMode, bool shuffle,
                         std::vector<int>& shuffledIndices, int& shuffleIndex);

    void execute() override;
    void undo() override;
    QString description() const override;

private:
    QMediaPlayer* player;
    std::list<QUrl>& playlist;
    std::list<QUrl>::iterator& currentTrack;
    std::list<QUrl>::iterator originalTrack;
    QStandardItemModel* model;
    RepeatMode repeatMode;
    bool shuffle;
    std::vector<int>& shuffledIndices;
    int& shuffleIndex;
};



class SetVolumeCommand : public Command {
public:
    SetVolumeCommand(QAudioOutput* audioOutput, int newVolume, int oldVolume);


    void execute() override ;

    void undo() override ;

    QString description() const override ;

private:
    QAudioOutput* audioOutput;
    int newVolume;
    int oldVolume;
};

class SeekCommand : public Command {
public:
    SeekCommand(QMediaPlayer* player, qint64 newPosition, qint64 oldPosition);

    void execute() override ;

    void undo() override ;

    QString description() const override ;


private:
    QMediaPlayer* player;
    qint64 newPosition;
    qint64 oldPosition;
};



class CreatePlaylistCommand : public Command
{

public:
    CreatePlaylistCommand(QMap<QString, std::list<QUrl>>& playlists, QStringListModel* playlistsModel, const QString& name);

    void execute() override ;


    void undo() override ;

    QString description() const override ;

private:
    QMap<QString, std::list<QUrl>>& playlists;
    QStringListModel* playlistsModel;
    QString name;
};



class DeletePlaylistCommand : public Command
{
public:
    DeletePlaylistCommand(QMap<QString, std::list<QUrl>>& playlists,QStringListModel* playlistsModel, const QString& name);

    void execute() override ;

    void undo() override ;

    QString description() const override ;

private:
    QMap<QString, std::list<QUrl>>& playlists;
    QStringListModel* playlistsModel;
    QString name;
    std::list<QUrl> playlistContent;
};



class SetRepeatModeCommand : public Command
{
public:
    SetRepeatModeCommand(RepeatMode& currentMode, RepeatMode newMode);

    void execute() override ;

    void undo() override ;

    QString description() const override ;

private:
    RepeatMode& currentMode;
    RepeatMode newMode;
    RepeatMode oldMode;
};


class ToggleShuffleCommand : public Command
 {
    bool& shuffleEnabled;
    std::list<QUrl>& playlist;
    std::list<QUrl>::iterator& currentTrack;
    std::list<QUrl>::iterator originalTrack;
    std::vector<int>& shuffledIndices;
    int& shuffleIndex;

public:
    ToggleShuffleCommand(bool& shuffleEnabled, std::list<QUrl>& playlist,
                         std::list<QUrl>::iterator& currentTrack,
                         std::vector<int>& shuffledIndices, int& shuffleIndex);

    void execute();
    void undo();
    QString description() const;
};




#endif // MUSICPLAYER_COMMANDS_H
