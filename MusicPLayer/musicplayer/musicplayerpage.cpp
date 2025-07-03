#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"


musicplayerpage::musicplayerpage(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::musicplayerpage)
{
    ui->setupUi(this);
    setIcon();
    setPlayer();
    setChat();
    setInternet();

    setupVisualizerUI();


    this->menuBar()->raise(); // مطمئن میشه منوبار بالاتر از همه ویجت‌هاست
    this->menuBar()->setEnabled(true);
    this->menuBar()->setVisible(true);
    settoolbar();

}

musicplayerpage::~musicplayerpage()
{
    delete player;
    delete audioOutput;
    delete chatDelegate;
    for (auto model : playlistModels) {
        delete model;
    }

    delete visualizer;
    delete visualizer2;
    delete ui;
}

void musicplayerpage::setIcon()
{
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
    ui->centralwidget->setStyleSheet("background-color: #EAECEE;");
    ui->generalListView->setStyleSheet("background-color: #FFFFFF;");
    ui->tabWidget->setStyleSheet("background-color: #D6EAF8;");
    ui->generalListView->setStyleSheet("background-color: #FFFFFF;");

}

void  musicplayerpage::setChat()
{
    chatDelegate = new ChatMessageDelegate(this);
    chatModel = new QStandardItemModel(this);
    chatLineEdit = new QLineEdit(this);
    chatLineEdit->setPlaceholderText("Enter your massage");
    sendButton = new QPushButton("send", this);
    chatLineEdit->hide();
    sendButton->hide();

    mainLayout = new QVBoxLayout(ui->generalListView);
    mainLayout->setContentsMargins(5,5,5,5);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(ui->generalListView);
    mainLayout->addStretch(1);

    QWidget* Container = new QWidget(this);
    QWidget* inputwiget = new QWidget(Container);
    inputLayout = new QHBoxLayout(inputwiget);
    inputLayout->setContentsMargins(0,0,0,0);

    chatLineEdit->setSizePolicy(QSizePolicy::Expanding ,QSizePolicy::Fixed);
    chatLineEdit->setFixedHeight(30);

    sendButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    sendButton->setFixedSize(60,30);

    inputLayout->addWidget(chatLineEdit);
    inputLayout->addWidget(sendButton);
    mainLayout->addWidget(inputwiget);

}

void musicplayerpage:: setPlayer()
{
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

}

 void musicplayerpage::setInternet()
{
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

     connect(tcpClient, &MyTcpClient::playSpecificSongRequested , this , &musicplayerpage::playSpecificSongRequested);
     connect(tcpServer, &MyTcpServer::playSpecificSongRequested , this , &musicplayerpage::playSpecificSongRequested);
     connect(tcpClient, &MyTcpClient::updateDeviceList,this, &musicplayerpage::updateDeviceList);
     connect(tcpServer, &MyTcpServer::updateDeviceList,this, &musicplayerpage::updateDeviceList);
     connect(tcpClient, &MyTcpClient::adminNameReceived, this, &musicplayerpage::onAdminNameReceived);
     connect(ui->generalListView, &QListView::customContextMenuRequested, this, &musicplayerpage::showUserContextMenu);

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
     this->installEventFilter(this);
     setMenuBar(ui->menubar);


}

void musicplayerpage::setupVisualizerUI()
{
    // ایجاد ویجت‌ها
    visualizer = new Visualizer(ui->graphicsView);
    visualizer2 = new Visualizer2(ui->graphicsView);

    // تنظیم combo box
    ui->comboBox->addItem("Album Cover", QVariant::fromValue(CoverMode));
    ui->comboBox->addItem("Visualizer 1", QVariant::fromValue(VisualizerMode1));
    ui->comboBox->addItem("Visualizer 2", QVariant::fromValue(VisualizerMode2));
    ui->comboBox->setCurrentIndex(0); // حالت پیش‌فرض: کاور آهنگ
    loadCoverOfMusic();

    // تنظیم اندازه و موقعیت
    visualizer->setFixedSize(ui->graphicsView->size());
    visualizer2->setFixedSize(ui->graphicsView->size());

    // اتصال signal
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &musicplayerpage::changeVisualizerMode);

    // حالت اولیه
    changeVisualizerMode(0);
}

void musicplayerpage::changeVisualizerMode(int index)
{
    // پنهان کردن همه ویجت‌ها
    visualizer->stop();
    visualizer->hide();
    visualizer2->stop();
    visualizer2->hide();

    // نمایش ویجت مورد نظر بر اساس انتخاب کاربر
    VisualizerMode mode = ui->comboBox->itemData(index).value<VisualizerMode>();

    switch(mode) {
    case CoverMode:
        // پاک کردن صحنه فعلی
        if (ui->graphicsView->scene()) {
            delete ui->graphicsView->scene();
        }
        loadCoverOfMusic();
        break;
    case VisualizerMode1:
        // پاک کردن صحنه کاور اگر وجود دارد
        if (ui->graphicsView->scene()) {
            delete ui->graphicsView->scene();
        }
        visualizer->start();
        visualizer->show();
        visualizer->setFixedSize(ui->graphicsView->size());
        break;
    case VisualizerMode2:
        // پاک کردن صحنه کاور اگر وجود دارد
        if (ui->graphicsView->scene()) {
            delete ui->graphicsView->scene();
        }
        visualizer2->start();
        visualizer2->show();
        visualizer2->setFixedSize(ui->graphicsView->size());
        break;
    }
}

void musicplayerpage::loadCoverOfMusic()
{
    VisualizerMode currentMode = ui->comboBox->currentData().value<VisualizerMode>();
    if (currentMode != CoverMode) {
        return;
    }

    auto  metaData = player->metaData();
    QVariant thumbVariant = metaData.value(QMediaMetaData::ThumbnailImage);
    QImage Default(":///image/image2.jpg");

    if(thumbVariant.isValid())
    {
        QImage image = thumbVariant.value<QImage>();
        if(!image.isNull())
        {
            QGraphicsScene * scene1 = new QGraphicsScene(this);
            QGraphicsPixmapItem *item = scene1->addPixmap(QPixmap::fromImage(image));
            ui->graphicsView->setScene(scene1);
            ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);

        }
        else
        {
            qDebug() << "image not available";
            QGraphicsScene * scene2 = new QGraphicsScene(this);
            QGraphicsPixmapItem *item = scene2->addPixmap(QPixmap::fromImage(Default));
            ui->graphicsView->setScene(scene2);
            ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);

        }


    }
    else
    {
        QGraphicsScene * scene3 = new QGraphicsScene(this);
        QGraphicsPixmapItem *item = scene3->addPixmap(QPixmap::fromImage(Default));
        ui->graphicsView->setScene(scene3);
        ui->graphicsView->fitInView(item,Qt::KeepAspectRatio);
    }

}

void musicplayerpage::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    // به روز رسانی اندازه ویژوالایزرها
    visualizer->setFixedSize(ui->graphicsView->size());
    visualizer2->setFixedSize(ui->graphicsView->size());

    // اگر حالت کاور فعال است، تصویر را مجددا تنظیم کن
    VisualizerMode currentMode = ui->comboBox->currentData().value<VisualizerMode>();
    if (currentMode == CoverMode) {
        loadCoverOfMusic();
    }
}
