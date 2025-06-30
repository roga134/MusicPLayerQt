#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionopen_file_triggered()
{
    try
    {
        QStringList files = QFileDialog::getOpenFileNames(this,tr("Select Music Files"),QDir::homePath(),tr("Audio Files (*.mp3 *.wav);;All Files (*)"));

        if (files.isEmpty())
        {
            return;
        }

        for (const QString& filePath : files)
        {
            QFileInfo info(filePath);
            if(!info.exists())
            {
                throw std::runtime_error("File does not exist");
            }

            QUrl track = QUrl::fromLocalFile(filePath);
            if(!track.isValid())
            {
                throw std::runtime_error("Invalid file URL");
            }

            execute_Command(std::make_unique<AddTrackCommand>(playlists[mainkey[indexPlaylist]], playlistModels, track , mainkey[indexPlaylist]));


            listsong[indexPlaylist]->setModel(playlistModels[mainkey[indexPlaylist]]);
        }
    }catch(const std::exception& e)
    {
        QMessageBox::critical(this, "Error", QString("Failed to open files: %1").arg(e.what()));
    }


}

void musicplayerpage::on_pushButton_files_clicked()
{
    ui->generalListView->setStyleSheet("");
    chatLineEdit->hide();
    sendButton->hide();
    chatActive = false;

    ui->generalListView->setModel(playlistModels[currentPlaylistName]);
    ui->generalListView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->generalListView->setSelectionBehavior(QAbstractItemView::SelectRows);

    fileclied = true;
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    ui->generalListView->setModel(fileSystemModel);
    ui->generalListView->setRootIndex(fileSystemModel->index(QDir::homePath()));
}

void musicplayerpage::save_playlist_to_file(const QModelIndex &index)
{
    QString filePath = fileSystemModel->filePath(index);

    if (fileSystemModel->isDir(index))
    {
        directoryHistory.push(ui->generalListView->rootIndex());
        forwardHistory.clear();
        ui->generalListView->setRootIndex(index);
    }
    else if (filePath.endsWith(".mp3", Qt::CaseInsensitive) || filePath.endsWith(".wav", Qt::CaseInsensitive))
    {
        QUrl track = QUrl::fromLocalFile(filePath);

        execute_Command(std::make_unique<AddTrackCommand>(playlists[mainkey[indexPlaylist]], playlistModels, track, mainkey[indexPlaylist]));

        listsong[indexPlaylist]->setModel(playlistModels[mainkey[indexPlaylist]]);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "This is not audio");
    }
}

void musicplayerpage::on_pushButton_home_clicked()
{
    try {
        if (fileclied) {
            if (!fileSystemModel) {
                throw std::runtime_error("File system model not initialized");
            }

            forwardHistory.clear();
            directoryHistory.push(ui->generalListView->rootIndex());

            QModelIndex homeIndex = fileSystemModel->index(QDir::homePath());
            if (!homeIndex.isValid()) {
                throw std::runtime_error("Failed to get home directory index");
            }

            ui->generalListView->setRootIndex(homeIndex);
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Navigation Error", e.what());
    }



}

void musicplayerpage::on_pushButton_forward_clicked()
{
    try
    {
        if (!forwardHistory.isEmpty())
        {
            directoryHistory.push(ui->generalListView->rootIndex());
            QModelIndex next = forwardHistory.pop();
            if (!next.isValid()) {
                throw std::runtime_error("Invalid forward index");
            }
            ui->generalListView->setRootIndex(next);

    }        }catch (const std::exception& e) {
        QMessageBox::warning(this, "Navigation Error", e.what());
    }


}

void musicplayerpage::on_pushButton_back_clicked()
{
    if (!directoryHistory.isEmpty())
    {
        forwardHistory.push(ui->generalListView->rootIndex());
        QModelIndex previous = directoryHistory.pop();
        ui->generalListView->setRootIndex(previous);
    }
}


void musicplayerpage::updateCurrentSongLabel()
{
    if (currentTrack != playlists[currentPlaylistName].end()) {
        QFileInfo fileInfo(currentTrack->toLocalFile());
        QString songName = fileInfo.baseName();
        ui->currentSongLabel->setText(QString("آهنگ در حال پخش: ") + songName);
    } else {
        ui->currentSongLabel->setText("No song playing");
    }
}
