#ifndef MUSICPLAYERPAGE_H
#define MUSICPLAYERPAGE_H

#include "musicplayer_commands.h"
#include "myudpserver.h"
#include "myudpclient.h"
#include "chatmessagedelegate.h"


QT_BEGIN_NAMESPACE
namespace Ui { class musicplayerpage; }
QT_END_NAMESPACE


class musicplayerpage : public QMainWindow
{
    Q_OBJECT

public:
   explicit musicplayerpage(QWidget *parent = nullptr);
    ~musicplayerpage();
    QStringList getAllTrackNames() const;
    void setinformation(QString firstName,QString lastName,QString username,QString email);
    QString GetUserName(){return username;}

private slots:
    void on_pushButton_play_clicked();

    void play_pause_network();


    void on_positionChanged(qint64 position);

    void on_durationChanged( qint64 duration);

    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);

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
    void on_actionexit_2_triggered();
    void on_actionDon_t_shuffel_triggered();
    void on_actionshuffel_all_triggered();

    void on_actionadd_playlist_triggered();
    void on_actionsave_playlist_triggered();
    void on_actionload_playlist_triggered();


    void on_pushButton_creatPlaylist_clicked();
    void onTabChanged(int index);

    void showContextMenu(const QPoint &pos);
    void addToQueueFromListView(QListView *listView, const QModelIndex &index);
    void createQueueTab();


    void on_pushButton_savePlaylist_clicked();

    void on_pushButton_loadPlaylist_clicked();

    void renamePlaylistTab(int index) ;

    void loadCoverOfMusic();

    void on_pushButton_mode3_clicked();

    void ChangeGraphicView(QPoint pos);

    void on_pushButton_server_clicked();

    void on_pushButton_client_clicked();

    void on_pushButton_chat_clicked();

    void addChatMessage(const QString &message, bool isMyMessage);

    void on_pushButton_info_clicked();

    void on_actionUndo_triggered();

    void settoolbar();

    void on_actionDon_t_repeat_triggered();

    void on_actionrepeat_trak_triggered();

    void on_actionrepeat_playlist_triggered();

private:
    Ui::musicplayerpage *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    std::vector<QStandardItemModel*> listModels;


    std::vector<int> shuffledIndices;
    int shuffleIndex = 0;    

    std::map<QString ,std::list<QUrl>> playlists;
    QMap<QString, QStandardItemModel*> playlistModels;
    std::list<QUrl>::iterator currentTrack ;
    std::list<QUrl>::iterator lastTrack;


    RepeatMode repeatMode = NoRepeat;
    QString currentPlaylistName;
    bool shuffleMode = false ;
    bool muted = false ;
    int previousVolume = 50 ;

    std::stack<std::unique_ptr<Command>> undoStack ;

    QFileSystemModel *fileSystemModel;
    QStack<QModelIndex> directoryHistory;
    QStack<QModelIndex> forwardHistory;
    bool fileclied = false;

    void execute_Command(std::unique_ptr<Command> command);
    void play_current_track();
    QString formatTime(qint64 milliseconds);

    QListView* queueListView = nullptr;
    QStandardItemModel* queueModel = nullptr;
    int queueTabIndex = -1;
    std::queue<QUrl> temporary;

    std::vector<QListView*> listsong;
    int countPlaylist = 0;
    int indexPlaylist = 0;
    QMap<int, QString> mainkey;

    void updateCurrentSongLabel();

    QStringList logMessages;
    QStandardItemModel *logmodel = nullptr;
    void addLogMessage(const QString &msg);

    MyTcpServer *tcpServer;
    MyTcpClient *tcpClient;
    int is_server = 0;
    QSet<QTcpSocket*> clients;
    void handleplaybutton();

    QPushButton *sendButton = nullptr;
    QLineEdit *chatLineEdit = nullptr;
    bool chatActive = false;
    QStandardItemModel *chatModel =nullptr;
    ChatMessageDelegate *chatDelegate;
    QWidget* chatContainer;
    QVBoxLayout *mainLayout;
    QHBoxLayout * inputLayput;

    QString firstName, lastName, username, email;
    ChatMessageDelegate *infotDelegate;
    QStandardItemModel *infotModel ;


    void keyPressEvent(QKeyEvent *event);
    bool ctrlMPressed = false;
};

#endif
