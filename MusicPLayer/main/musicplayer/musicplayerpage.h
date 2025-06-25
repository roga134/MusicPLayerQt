#ifndef MUSICPLAYERPAGE_H
#define MUSICPLAYERPAGE_H

#include "musicplayer_commands.h"


QT_BEGIN_NAMESPACE
namespace Ui { class musicplayerpage; }
QT_END_NAMESPACE


class musicplayerpage : public QMainWindow
{
    Q_OBJECT

public:
   explicit musicplayerpage(QWidget *parent = nullptr);
    ~musicplayerpage();

private slots:

    void on_pushButton_play_clicked();


//     void on_pushButton_stop_clicked();

//     void on_pushButton_remove_clicked();

//     void on_volumesSlider_valueChanges();

//     void on_pushButton_mute_clicked();

//     void on_pushButton_shuffle_clicked();

//     void on_pushButton_repeat_clicked();

//     void on_pushButton_undo_clicked();

//     void on_pushButton_redo_clicked();

//     void on_positionChanged(qint64 position);

//     void on_durationChanged( qint64 duration);

//     void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);

//     void on_addTo_QueueButton_clicked();

//     void on_clear_QueueButton_clicked();

//     void on_create_PlayListButton_clicked();

     void on_actionAdd_Track_triggered();

    void on_pushButton_prev_clicked();

     void on_pushButton_next_clicked();

 private:
    Ui::musicplayerpage *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QStandardItemModel *playlistModel ;
     bool isPlay = false ;

    std::map<QString ,std::list<QUrl>> playlists;
    std::list<QUrl>::iterator currentTrack ;
    std::queue<QUrl> temporary;


    RepeatMode repeatMode = NoRepeat;
    QString currentPlaylistName;
    bool shuffleMode = false ;
    bool muted = false ;
    int previousVolume = 50 ;

    std::stack<std::unique_ptr<Command>> undoStack ;
    std::stack<std::unique_ptr<Command>> redoStack ;



    void execute_Command(std::unique_ptr<Command> command);
//     void update_undo_and_redo_Button();
//     void update_playlistUI();
    void play_current_track();
//     void shuffle_Playlist();
//     QString formatTime(qint64 milliseconds);
//     std::list<QUrl>::iterator find_in_playlist(const QUrl& url);
  //  void save_playlist_to_file();
   // void load_playlists_from_file();
   //void handle_media_error(const QString errorMessage);

};

#endif
