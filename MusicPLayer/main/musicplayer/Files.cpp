#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionopen_file_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,tr("Select Music Files"),QDir::homePath(),tr("Audio Files (*.mp3 *.wav);;All Files (*)"));

    if (files.isEmpty())
    {
        return;
    }

    for (const QString& filePath : files)
    {
        QFileInfo info(filePath);

        QUrl track = QUrl::fromLocalFile(filePath);

        execute_Command(std::make_unique<AddTrackCommand>(playlists[mainkey[indexPlaylist]], playlistModels, track , mainkey[indexPlaylist]));


        listsong[indexPlaylist]->setModel(playlistModels[mainkey[indexPlaylist]]);
    }
}

void musicplayerpage::on_pushButton_files_clicked()
{
    fileclied = true;
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    ui->playlist->setModel(fileSystemModel);
    ui->playlist->setRootIndex(fileSystemModel->index(QDir::homePath()));
}

void musicplayerpage::save_playlist_to_file(const QModelIndex &index)
{
    QString filePath = fileSystemModel->filePath(index);

    if (fileSystemModel->isDir(index))
    {
        directoryHistory.push(ui->playlist->rootIndex());
        forwardHistory.clear();
        ui->playlist->setRootIndex(index);
    }
    else if (filePath.endsWith(".mp3", Qt::CaseInsensitive) || filePath.endsWith(".wav", Qt::CaseInsensitive))
    {
        QUrl track = QUrl::fromLocalFile(filePath);

        execute_Command(std::make_unique<AddTrackCommand>(playlists[mainkey[indexPlaylist]], playlistModels, track, mainkey[indexPlaylist]));

        listsong[indexPlaylist]->setModel(playlistModels[mainkey[indexPlaylist]]);
        decoder->setSource(track);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "This is not audio");
    }
}

void musicplayerpage::on_pushButton_home_clicked()
{
    if(fileclied)
    {
        forwardHistory.clear();
        directoryHistory.push(ui->playlist->rootIndex());

        QModelIndex homeIndex = fileSystemModel->index(QDir::homePath());
        ui->playlist->setRootIndex(homeIndex);
    }
    else
    {
        // یه چی خودت بزار که انگار باز نشده
    }
}

void musicplayerpage::on_pushButton_forward_clicked()
{
    if (!forwardHistory.isEmpty())
    {
        directoryHistory.push(ui->playlist->rootIndex());
        QModelIndex next = forwardHistory.pop();
        ui->playlist->setRootIndex(next);
    }
}

void musicplayerpage::on_pushButton_back_clicked()
{
    if (!directoryHistory.isEmpty())
    {
        forwardHistory.push(ui->playlist->rootIndex());
        QModelIndex previous = directoryHistory.pop();
        ui->playlist->setRootIndex(previous);
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
