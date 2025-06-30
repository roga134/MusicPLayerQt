#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_pushButton_creatPlaylist_clicked()
{
    QWidget *newTab = new QWidget();

    QListView *listView = new QListView(newTab);
    QStandardItemModel *newModel = new QStandardItemModel(this);
    newModel->setHorizontalHeaderLabels({"Track", "Duration"});

    listView->setModel(newModel);

    listsong.push_back(listView);
    listModels.push_back(newModel);

    connect(listView, &QListView::doubleClicked, this, [=](const QModelIndex &index) {
        this->handleDoubleClickFromListView(listView, index);
    });

    connect(listView, &QListView::doubleClicked, this, &musicplayerpage::onItemDoubleClicked);

    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listView , &QListView::customContextMenuRequested , this , &musicplayerpage::showContextMenu);

    QString key = QString("PlayList %1").arg(countPlaylist+1);
    playlistModels[key] = newModel;
    playlists[key] = std::list<QUrl>();

    QVBoxLayout *layout = new QVBoxLayout(newTab);
    layout->addWidget(listView);
    newTab->setLayout(layout);

    int index = ui->tabWidget->addTab(newTab, key);
    ui->tabWidget->setCurrentIndex(index);

    mainkey[countPlaylist] = key;

    countPlaylist++;
    indexPlaylist = countPlaylist - 1;

    currentPlaylistName = key;
    currentTrack = playlists[key].end();
}

void musicplayerpage::onTabChanged(int index)
{
    if (index >= 0 && index < listsong.size() && index < listModels.size())
    {
        indexPlaylist = index;

        QListView *currentListView = listsong[index];
        QStandardItemModel *currentModel = listModels[index];

        currentListView->setModel(currentModel);
    }
}


void musicplayerpage::on_pushButton_savePlaylist_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Playlist", "", "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    if (!filePath.endsWith(".json", Qt::CaseInsensitive))
    {
        filePath += ".json";
    }

    int currentIndex = ui->tabWidget->currentIndex();
    QString currentPlaylistName = ui->tabWidget->tabText(currentIndex);

    if (playlists.find(currentPlaylistName) == playlists.end())
    {
        QMessageBox::warning(this, "Error", "Current playlist not found.");
        return;
    }

    QJsonObject rootObj;
    QJsonArray trackArray;

    for (const QUrl& trackUrl : playlists[currentPlaylistName])
    {
        trackArray.append(trackUrl.toString());
    }

    rootObj[currentPlaylistName] = trackArray;

    QJsonDocument doc(rootObj);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Error", "Cannot open file to save playlist.");
        return;
    }

    file.write(doc.toJson());
    file.close();

    QMessageBox::information(this, "Success", "Playlist saved successfully.");
}


void musicplayerpage::on_pushButton_loadPlaylist_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Load Playlists", "", "JSON Files (*.json)");
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error", "Cannot open file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
    {
        QMessageBox::warning(this, "Error", "Invalid playlist file.");
        return;
    }

    QJsonObject rootObj = doc.object();

    for (QString key : rootObj.keys())
    {
        if (key.compare("Default", Qt::CaseInsensitive) == 0 || key.startsWith("Default (", Qt::CaseInsensitive))
            continue;

        QString uniqueKey = key;
        int suffix = 1;
        while (playlists.find(uniqueKey) != playlists.end())
            uniqueKey = QString("%1 (%2)").arg(key).arg(suffix++);

        QWidget *newTab = new QWidget();
        QListView *listView = new QListView(newTab);
        QStandardItemModel *newModel = new QStandardItemModel(this);

        playlists[uniqueKey] = std::list<QUrl>();
        playlistModels[uniqueKey] = newModel;

        QJsonArray trackArray = rootObj[key].toArray();
        for (const QJsonValue &value : trackArray)
        {
            QUrl track = QUrl(value.toString());
            execute_Command(std::make_unique<AddTrackCommand>(playlists[uniqueKey], playlistModels, track, uniqueKey));

            listsong[indexPlaylist]->setModel(playlistModels[mainkey[indexPlaylist]]);
        }

        listView->setModel(newModel);

        listsong.push_back(listView);
        listModels.push_back(newModel);

        connect(listView, &QListView::doubleClicked, this, [=](const QModelIndex &index)
                {
                    this->handleDoubleClickFromListView(listView, index);
                });

        connect(listView, &QListView::doubleClicked, this, &musicplayerpage::onItemDoubleClicked);

        QVBoxLayout *layout = new QVBoxLayout(newTab);
        layout->addWidget(listView);
        newTab->setLayout(layout);

        int tabIndex = ui->tabWidget->addTab(newTab, uniqueKey);
        ui->tabWidget->setCurrentIndex(tabIndex);

        mainkey[countPlaylist] = uniqueKey;
        countPlaylist++;
        indexPlaylist = countPlaylist - 1;
    }

    QMessageBox::information(this, "Success", "Playlists loaded successfully.");
}

void musicplayerpage::renamePlaylistTab(int index)
{
    try
    {
        if (index < 0 || index >= ui->tabWidget->count())
            return;

        QString oldName = ui->tabWidget->tabText(index);
        QString newName = QInputDialog::getText(this, "Rename Playlist","Enter new playlist name:", QLineEdit::Normal, oldName);

        if (!newName.isEmpty() && newName != oldName)
        {
            if (playlists.find(newName) != playlists.end())
            {
                throw std::runtime_error("playlist name already exists");
            }

            ui->tabWidget->setTabText(index, newName);

            auto it = playlists.find(oldName);
            if (it != playlists.end())
            {
                playlists[newName] = std::move(it->second);
                playlists.erase(it);
            }

            if (playlistModels.contains(oldName))
            {
                playlistModels[newName] = playlistModels[oldName];
                playlistModels.remove(oldName);
            }

            for (auto it = mainkey.begin(); it != mainkey.end(); ++it)
            {
                if (it.value() == oldName)
                {
                    it.value() = newName;
                    break;
                }
            }

            if (currentPlaylistName == oldName)
                currentPlaylistName = newName;

            qDebug() << "Playlist renamed from" << oldName << "to" << newName;
        }
    }catch(const std::exception& e)
    {
        QMessageBox::warning(this,"Error",QString(e.what()));
    }
}

void musicplayerpage::showContextMenu(const QPoint &pos)
{
    QListView *listView = qobject_cast<QListView*>(sender());
    if (!listView) return;

    QModelIndex index = listView->indexAt(pos);
    if (!index.isValid()) return;

    QMenu contextMenu(this);
    QAction *addToQueueAction = contextMenu.addAction("Add to Queue");

    connect(addToQueueAction, &QAction::triggered, this, [this, listView, index]() {
        this->addToQueueFromListView(listView, index);
    });

    contextMenu.exec(listView->viewport()->mapToGlobal(pos));
}

void musicplayerpage::addToQueueFromListView(QListView *listView, const QModelIndex &index)
{
    try
    {
        QString playlistName;

        for (const auto& key : playlistModels.keys())
        {
            if (playlistModels[key] == listView->model())
            {
                playlistName = key;
                break;
            }
        }

        if (playlistName.isEmpty()) return;

        auto& playlist = playlists[playlistName];
        int row = index.row();
        if (row < 0 || row >= static_cast<int>(playlist.size()))
            throw std::out_of_range("Invalid track index");

        auto it = playlist.begin();
        std::advance(it, row);

        temporary.push(*it);

        if (!queueListView) {
            createQueueTab();
        }

        QStandardItem *item = new QStandardItem(it->fileName());
        if(!item)
            throw std::bad_alloc();

        item->setData(it->toString(), Qt::UserRole);
        queueModel->appendRow(item);

        if (player->playbackState() != QMediaPlayer::PlayingState && temporary.size() == 1) {
            QUrl nextTrack = temporary.front();
            player->setSource(nextTrack);
            player->play();
            updateCurrentSongLabel();
        }

        QMessageBox::information(this, "Added to Queue", "Track added to temporary queue");
    }catch(const std::exception& e)
    {
        QMessageBox::critical(this,"Error","Failed to add to queue");

    }
}


void musicplayerpage::createQueueTab()
{
    QWidget *queueTab = new QWidget();

    queueListView = new QListView(queueTab);
    queueModel = new QStandardItemModel(queueListView);

    queueListView->setModel(queueModel);

    QVBoxLayout *layout = new QVBoxLayout(queueTab);
    layout->addWidget(queueListView);
    queueTab->setLayout(layout);

    queueTabIndex = ui->tabWidget->addTab(queueTab, "Queue");
    ui->tabWidget->setCurrentIndex(queueTabIndex);
}

void musicplayerpage::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status != QMediaPlayer::EndOfMedia)
        return;

    if (!temporary.empty())
    {
        QUrl nextTrack = temporary.front();
        temporary.pop();

        player->setSource(nextTrack);
        player->play();
        QFileInfo fileInfo(nextTrack.toLocalFile());
        QString songName = fileInfo.baseName();
        ui->currentSongLabel->setText(QString("آهنگ در حال پخش: ") + songName);
        if (temporary.empty() && queueModel)
            queueModel->clear();

        return;
    }

    if (repeatMode == RepeatMode::RepreatOne)
    {
        if (player && currentTrack != playlists[currentPlaylistName].end())
        {
            player->setSource(*currentTrack);
            player->play();
            updateCurrentSongLabel();
            return;
        }
    }

    if (!currentPlaylistName.isEmpty() && currentTrack != playlists[currentPlaylistName].end())
    {
        ++currentTrack;
        if (currentTrack != playlists[currentPlaylistName].end())
        {
            player->setSource(*currentTrack);
            player->play();
            updateCurrentSongLabel();
            return;
        }
    }

    player->stop();
    ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
    ui->label_played->setText("00:00");
    ui->label_remaning->setText("00:00");
    ui->time->setValue(0);
    updateCurrentSongLabel();
}

