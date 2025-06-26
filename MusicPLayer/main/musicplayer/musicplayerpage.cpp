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
    ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle-off.png"));
    ui->pushButton_back->setIcon(QIcon(":/icons/image/back.png"));
    ui->pushButton_home->setIcon(QIcon(":/icons/image/home.png"));
    ui->pushButton_forward->setIcon(QIcon(":/icons/image/forward.png"));
    ui->label_played->setMinimumWidth(40);
    ui->label_remaning->setMinimumWidth(40);
    ui->label_played->setText("00:00");
    ui->label_remaning->setText("00:00");

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    ui->volum->setValue(50);
    audioOutput->setVolume(0.5);
    player->setAudioOutput(audioOutput);


    // Setup Playlist Model
    playlistModel = new QStandardItemModel(this);
    ui->playlist->setModel(playlistModel);
    playlistModel = new QStandardItemModel(this);
    playlistModel->setHorizontalHeaderLabels({"Track", "Duration"});
    ui->playlist->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlist->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listSongs->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Initialize default playlist
    currentPlaylistName = "Default";
    playlists[currentPlaylistName] = std::list<QUrl>();
    currentTrack = playlists[currentPlaylistName].end();


    repeatMode = RepeatMode::NoRepeat;

    decoder = new QAudioDecoder(this);
    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(decoder, &QAudioDecoder::bufferReady, this, &musicplayerpage::processBuffer);
    connect(timer, &QTimer::timeout, this, &musicplayerpage::processBuffer);
    timer->start(50);

    connect(player, &QMediaPlayer::positionChanged, this, &musicplayerpage::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &musicplayerpage::on_durationChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &musicplayerpage::on_mediaStatusChanged);
    connect(ui->playlist, &QTreeView::doubleClicked, this, &musicplayerpage::save_playlist_to_file);
    connect(ui->listSongs, &QListView::doubleClicked, this, &musicplayerpage::onItemDoubleClicked);
    connect(ui->volum, &QSlider::valueChanged, this, &musicplayerpage::setvolum );

    setupVisualizerBars();
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

musicplayerpage::~musicplayerpage()
{
    delete player;
    delete audioOutput;
    delete playlistModel;
    delete ui;
}


/*
void musicplayerpage::on_pushButton_creatPlaylist_clicked()
{
    bool ok;
    QString playlistName = QInputDialog::getText(this, tr("Create Playlist"),
                                                 tr("Playlist Name:"), QLineEdit::Normal, "", &ok);
    if (playlists.find(playlistName) == playlists.end())
    {
        QTreeView *treeView = new QTreeView();
        QStandardItemModel *model = new QStandardItemModel(treeView);
        model->setHorizontalHeaderLabels({"Track", "Duration"});
        treeView->setModel(model);

        int tabIndex = ui->tabWidget->addTab(treeView, playlistName);
        ui->tabWidget->setCurrentIndex(tabIndex);

        playlists[playlistName] = std::list<QUrl>();
        currentPlaylistName = playlistName;

        //execute_Command(std::make_unique<CreatePlaylistCommand>(playlists, playlistsModel, playlistName));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"),
                             tr("Playlist with this name already exists!"));
    }

}*/
