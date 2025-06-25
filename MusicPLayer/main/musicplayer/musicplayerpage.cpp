#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"


musicplayerpage::musicplayerpage(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::musicplayerpage)
{
    ui->setupUi(this);
    ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
    ui->pushButton_next->setIcon(QIcon(":/icons/image/prev.png"));
    ui->pushButton_prev->setIcon(QIcon(":/icons/image/next.png"));
    ui->pushButton_mute->setIcon(QIcon(":/icons/image/unmute.png"));
    ui->pushButton_mode->setIcon(QIcon(":/icons/image/shuffle-off.png"));
    ui->label_played->setMinimumWidth(40);
    ui->label_remaning->setMinimumWidth(40);
    ui->label_played->setText("00:00");
    ui->label_remaning->setText("00:00");



    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // Setup Playlist Model
    playlistModel = new QStandardItemModel(this);
    ui->playlist->setModel(playlistModel);
   playlistModel = new QStandardItemModel(this);
   playlistModel->setHorizontalHeaderLabels({"Track", "Duration"});
   ui->playlist->setModel(playlistModel);
   ui->playlist->setSelectionMode(QAbstractItemView::SingleSelection);
   ui->playlist->setSelectionBehavior(QAbstractItemView::SelectRows);


    // Initialize default playlist
    currentPlaylistName = "Default";
    playlists[currentPlaylistName] = std::list<QUrl>();
    currentTrack = playlists[currentPlaylistName].end();


    repeatMode = RepeatMode::NoRepeat;

}

musicplayerpage::~musicplayerpage()
{
    delete player;
    delete audioOutput;
    delete playlistModel;
    delete ui;
}


