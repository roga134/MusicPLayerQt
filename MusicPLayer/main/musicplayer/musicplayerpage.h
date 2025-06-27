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


//     void on_pushButton_repeat_clicked();

//     void on_pushButton_undo_clicked();

//     void on_pushButton_redo_clicked();

    void on_positionChanged(qint64 position);

    void on_durationChanged( qint64 duration);

    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);

//     void on_addTo_QueueButton_clicked();

//     void on_clear_QueueButton_clicked();

//     void on_create_PlayListButton_clicked();

     void on_actionAdd_Track_triggered();

    void on_pushButton_prev_clicked();

     void on_pushButton_next_clicked();

    void on_actionRemove_Track_triggered();

     void on_pushButton_mute_clicked();

    void on_volum_valueChanged(int value);


    void on_time_sliderMoved(int position);

    void on_pushButton_shufle_clicked();

    void on_pushButton_files_clicked();

    void save_playlist_to_file(const QModelIndex &index);

    void on_pushButton_back_clicked();

    void on_actionopen_file_triggered();

    void onItemDoubleClicked(const QModelIndex &index);
    void handleDoubleClickFromListView(QListView *listView, const QModelIndex &index);

    void setvolum(int value);

    void on_pushButton_home_clicked();

    void on_pushButton_forward_clicked();

    void on_actionprevios_song_triggered();
    void on_actionplay_triggered();
    void on_actionnext_trak_triggered();
    void on_actionexit_triggered();
    void on_actionDon_t_shuffel_triggered();
    void on_actionshuffel_all_triggered();

    void on_actionadd_playlist_triggered();
    void on_actionsave_playlist_triggered();
    void on_actionload_playlist_triggered();

    void processBuffer();
    void updateVisualizer();
    void setupVisualizerBars();
    void showEvent(QShowEvent *event);

    void on_pushButton_creatPlaylist_clicked();
    void onTabChanged(int index);

    void on_pushButton_savePlaylist_clicked();

    void on_pushButton_loadPlaylist_clicked();

    void updateQueueTab();
    void createQueueTab();
    void renamePlaylistTab(int index) ;

private:
    Ui::musicplayerpage *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    std::vector<QStandardItemModel*> listModels;

    QString audioFilePath;
    QAudioDecoder *decoder;
    QGraphicsScene *scene;
    QTimer *timer;
    QList<QGraphicsRectItem*> bars;
    double currentAmplitude = 0;
    double displayedAmplitude = 0;
    QVector<double> currentBands;



    std::vector<int> shuffledIndices;
    int shuffleIndex = 0;    

    std::map<QString ,std::list<QUrl>> playlists;
    QMap<QString, QStandardItemModel*> playlistModels;
    std::list<QUrl>::iterator currentTrack ;
    std::list<QUrl>::iterator lastTrack;
    std::queue<QUrl> temporary;


    RepeatMode repeatMode = NoRepeat;
    QString currentPlaylistName;
    bool shuffleMode = false ;
    bool muted = false ;
    int previousVolume = 50 ;

    std::stack<std::unique_ptr<Command>> undoStack ;
    std::stack<std::unique_ptr<Command>> redoStack ;

    QFileSystemModel *fileSystemModel;
    QStack<QModelIndex> directoryHistory;
    QStack<QModelIndex> forwardHistory;
    bool fileclied = false;

    void execute_Command(std::unique_ptr<Command> command);
    void play_current_track();
    QString formatTime(qint64 milliseconds);

    std::vector<QListView*> listsong;
    QListView* queueListView;
    QStandardItemModel* queueModel;
    int queueTabIndex;
    int countPlaylist = 0;
    int indexPlaylist = 0;
    QMap<int, QString> mainkey;
    QMap<QString, MusicPlayerQueue> playlistQueues;
};

#endif
