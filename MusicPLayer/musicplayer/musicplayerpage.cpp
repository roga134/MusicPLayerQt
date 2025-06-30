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
    ui->pushButton_creatPlaylist->setIcon(QIcon(":/icons/image/add_playlist.png"));
    ui->pushButton_loadPlaylist->setIcon(QIcon(":/icons/image/load_playlist.png"));
    ui->pushButton_savePlaylist->setIcon(QIcon(":/icons/image/save_playlist.png"));
    ui->pushButton_mode3->setIcon(QIcon(":/icons/image/no-repeat.png"));
    ui->currentSongLabel->setText("آهنگ در حال پخش: -");
    ui->label_played->setMinimumWidth(40);
    ui->label_remaning->setMinimumWidth(40);
    ui->label_played->setText("00:00");
    ui->label_remaning->setText("00:00");
    ui->tabWidget->setTabText(countPlaylist, QString::fromStdString("PlayList " + std::to_string(countPlaylist + 1)));


    ClickableGraphicsView* newView = new ClickableGraphicsView(this);
    ui->horizontalLayout->replaceWidget(ui->graphicsView, newView);
    delete ui->graphicsView;
    ui->graphicsView = newView;


    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    ui->volum->setValue(50);
    audioOutput->setVolume(0.5);
    ui->volum->setRange(0, 100);
    player->setAudioOutput(audioOutput);

    playlistModels[currentPlaylistName] = new QStandardItemModel(this);
    playlistModels[currentPlaylistName]->setHorizontalHeaderLabels({"Track", "Duration"});
    currentPlaylistName = "Default";
    playlists[currentPlaylistName] = std::list<QUrl>();
    currentTrack = playlists[currentPlaylistName].end();

    repeatMode = RepeatMode::NoRepeat;

    on_pushButton_creatPlaylist_clicked();


    connect(player, &QMediaPlayer::positionChanged, this, &musicplayerpage::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &musicplayerpage::on_durationChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &musicplayerpage::on_mediaStatusChanged);
    connect(ui->generalListView, &QTreeView::doubleClicked, this, &musicplayerpage::save_playlist_to_file);
    connect(ui->volum, &QSlider::valueChanged, this, &musicplayerpage::setvolum );
    connect(ui->tabWidget, &QTabWidget::currentChanged,this, &musicplayerpage::onTabChanged);
    connect(ui->tabWidget->tabBar(), &QTabBar::tabBarDoubleClicked,this, &musicplayerpage::renamePlaylistTab);
    connect(player, &QMediaPlayer::metaDataChanged, this, &musicplayerpage::loadCoverOfMusic);

    auto view = qobject_cast<ClickableGraphicsView*>(ui->graphicsView);
    if (view)
    {
        connect(view, &ClickableGraphicsView::clicked, this, &musicplayerpage::ChangeGraphicView);
    }

    infotDelegate = new ChatMessageDelegate(this);
    infotModel = new QStandardItemModel(this);

    logmodel = new QStandardItemModel(this);

    tcpServer = new MyTcpServer(this);

    connect(tcpServer, &MyTcpServer::logMessage, this, [this](const QString &msg) {
        addLogMessage(msg);
    });

    tcpClient = new MyTcpClient(this);
    tcpClient->setMusicPlayerPage(this);

    connect(tcpClient, &MyTcpClient::logMessage, this, [this](const QString &msg) {
        addLogMessage(msg);
    });

    connect(tcpServer, &MyTcpServer::playMusicRequested,this, &musicplayerpage::play_pause_network);
    connect(tcpClient, &MyTcpClient::playMusicRequestedclient,this, &musicplayerpage::play_pause_network);

    chatDelegate = new ChatMessageDelegate(this);

    chatModel = new QStandardItemModel(this);
    chatLineEdit = new QLineEdit(this);
    chatLineEdit->setPlaceholderText("Enter your massage");
    sendButton = new QPushButton("send", this);
    chatLineEdit->hide();
    sendButton->hide();
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->generalListView);
    mainLayout->addWidget(ui->generalListView);

    QHBoxLayout * inputLayput = new QHBoxLayout;
    chatLineEdit->setSizePolicy(QSizePolicy::Expanding ,QSizePolicy::Fixed);
    chatLineEdit->setFixedHeight(30);
    /*
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendMessageButton);
    inputLayout->setStretch(0, 1);

    QVBoxLayout *networkLayout = new QVBoxLayout(networkTab);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(chatDisplay);
    networkLayout->addWidget(scrollArea);
    networkLayout->setStretch(0, 1);
    networkLayout->addLayout(inputLayout);
    */
    sendButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    sendButton->setFixedSize(60,30);
    inputLayput->addWidget(chatLineEdit);
    inputLayput->addWidget(sendButton);
    mainLayout->addLayout(inputLayput);

    connect(tcpServer, &MyTcpServer::messageReceived, this, [this](const QString &msg, const QString &sender) {
        QMetaObject::invokeMethod(this,[this,msg,sender]()
                                  {
                                      if(chatActive){
                                          addChatMessage(sender + ": " + msg, false);
                                      }
                                      else
                                      {
                                          addLogMessage(sender +":"+msg);
                                      }

                                  },Qt::QueuedConnection);
    });

    connect(tcpClient, &MyTcpClient::messageReceived, this, [this](const QString &msg, const QString &sender) {
        QMetaObject::invokeMethod(this,[this,msg,sender]()
                                  {
                                      if(chatActive){
                                          addChatMessage(sender + ": " + msg, false);
                                      }
                                      else
                                      {
                                          addLogMessage(sender +":"+msg);
                                      }

                                  },Qt::QueuedConnection);
    });
}

musicplayerpage::~musicplayerpage()
{
    delete player;
    delete audioOutput;
    delete chatDelegate;
    for (auto model : playlistModels) {
        delete model;
    }
    delete ui;
}

void musicplayerpage::ChangeGraphicView(QPoint pos)
{

}
