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
    if (index < 0 || index >= ui->tabWidget->count())
        return;

    QString oldName = ui->tabWidget->tabText(index);
    QString newName = QInputDialog::getText(this, "Rename Playlist","Enter new playlist name:", QLineEdit::Normal, oldName);

    if (!newName.isEmpty() && newName != oldName)
    {
        if (playlists.find(newName) != playlists.end())
        {
            QMessageBox::warning(this, "Error", "A playlist with this name already exists.");
            return;
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
}

