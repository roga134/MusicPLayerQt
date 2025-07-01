#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionAdd_Track_triggered()
{
    QUrl trackUrl = QFileDialog::getOpenFileUrl(this, "Select Audio File", QUrl::fromLocalFile(QDir::homePath()),  "(*.*) All Files");
    try
    {
        if (!trackUrl.isValid() || trackUrl.isEmpty())
        {
            throw std::runtime_error("No file select");
        }
        if(!QFile::exists(trackUrl.toLocalFile()))
        {
            throw std::runtime_error("file does not exit");
        }
        execute_Command(std::make_unique<AddTrackCommand>(playlists[currentPlaylistName], playlistModels, trackUrl , mainkey[indexPlaylist]));


        if (currentTrack == playlists[currentPlaylistName].end())
        {
            currentTrack = playlists[currentPlaylistName].begin();
        }

    }catch(const std::exception& e)
    {
        qDebug()<<"Exception in on_actionAdd_Track_triggered " << e.what();
    }
}

void musicplayerpage::on_pushButton_mode3_clicked()
{
    RepeatMode newMode;
    if (repeatMode == RepeatMode::NoRepeat)
    {
        newMode = RepeatMode::RepeatAll;
        ui->pushButton_mode3->setIcon(QIcon(":/icons/image/repeat.png"));
    }
    else if (repeatMode == RepeatMode::RepeatAll)
    {
        newMode = RepeatMode::RepreatOne;
        ui->pushButton_mode3->setIcon(QIcon(":/icons/image/repeat-one.png"));
    }
    else
    {
        newMode = RepeatMode::NoRepeat;
        ui->pushButton_mode3->setIcon(QIcon(":/icons/image/no-repeat.png"));
    }
    execute_Command(std::make_unique<SetRepeatModeCommand>(repeatMode, newMode));
}


void musicplayerpage::on_pushButton_play_clicked()
{
    if(ispause)
    {
        ispause = false;
    }
    else
    {
        ispause = true;
    }

    handleplaybutton();
    if (player->playbackState() == QMediaPlayer::PlayingState)
    {
        execute_Command(std::make_unique<PauseCommand>(player));
        ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
    }
    else
    {
        if(currentTrack == playlists[currentPlaylistName].end())
        {
            currentTrack = playlists[currentPlaylistName].begin();
            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            lastTrack = currentTrack;
            ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));

            updateCurrentSongLabel();
            return;
        }

        if (!playlists[currentPlaylistName].empty())
        {
            auto currentTrackUrl = *currentTrack;

            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            lastTrack = currentTrack;
            ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));

            updateCurrentSongLabel();

        }
    }
}

void musicplayerpage::play_pause_network()
{
    if (player->playbackState() == QMediaPlayer::PlayingState)
    {
        execute_Command(std::make_unique<PauseCommand>(player));
        ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
    }
    else
    {
        if(currentTrack == playlists[currentPlaylistName].end())
        {
            currentTrack = playlists[currentPlaylistName].begin();
            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            lastTrack = currentTrack;
            ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));

            updateCurrentSongLabel();
            return;
        }

        if (!playlists[currentPlaylistName].empty())
        {
            auto currentTrackUrl = *currentTrack;

            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            lastTrack = currentTrack;
            ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));

            updateCurrentSongLabel();

        }
    }
}

void musicplayerpage::onItemDoubleClicked(const QModelIndex &index)
{
    if(ispause)
    {
        ispause = false;
    }
    else
    {
        ispause = true;
    }
    handleplaybutton();
    auto &playlist = playlists[currentPlaylistName];
    int row = index.row();

    if(row < 0 || row >= static_cast<int>(playlist.size()))
    {
        qDebug() << "Double clicked invalid index";
        return;
    }

    auto it = playlist.begin();
    std::advance(it, row);
    currentTrack = it;

    execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
    updateCurrentSongLabel();
    lastTrack = currentTrack;
    ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));
}

void musicplayerpage::handleDoubleClickFromListView(QListView *listView, const QModelIndex &index)
{
    QString matchedPlaylistName;
    for (auto it = playlistModels.begin(); it != playlistModels.end(); ++it)
    {
        if (listView->model() == it.value())
        {
            matchedPlaylistName = it.key();
            break;
        }
    }

    if (matchedPlaylistName.isEmpty()) {
        qDebug() << "Playlist not found for this listView.";
        return;
    }

    auto &playlist = playlists[matchedPlaylistName];
    int row = index.row();

    if (row < 0 || row >= static_cast<int>(playlist.size()))
    {
        qDebug() << "Invalid index in playlist.";
        return;
    }

    currentTrack = playlist.begin();
    std::advance(currentTrack, row);
    currentPlaylistName = matchedPlaylistName;

    execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
    lastTrack = currentTrack;
    ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));
}


void musicplayerpage::execute_Command(std::unique_ptr<Command> command)
{
    try
    {
        command->execute();
        undoStack.push(std::move(command));
    }catch(const std::exception &e)
    {
        qDebug() <<"Command execution failed :" <<  e.what();
    }
}

void musicplayerpage::on_pushButton_prev_clicked()
{
    execute_Command(std::make_unique<PreviousTrackCommand>(
        player,
        playlists[currentPlaylistName],
        currentTrack,
        repeatMode,
        shuffleMode,
        shuffledIndices,
        shuffleIndex
        ));

    updateCurrentSongLabel();

    int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
    listsong[indexPlaylist]->setCurrentIndex(playlistModels[currentPlaylistName]->index(row, 0));
}


void musicplayerpage::on_pushButton_next_clicked()
{
    if (playlists.find(currentPlaylistName) == playlists.end() ||
        playlists[currentPlaylistName].empty()) {
        return;
    }

    execute_Command(std::make_unique<NextTrackCommand>(
        player,
        playlists[currentPlaylistName],
        currentTrack,
        repeatMode,
        shuffleMode,
        shuffledIndices,
        shuffleIndex
        ));

    updateCurrentSongLabel();

    int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
    listsong[indexPlaylist]->setCurrentIndex(playlistModels[currentPlaylistName]->index(row, 0));
}

void musicplayerpage::on_actionRemove_Track_triggered()
{
    QListView *listView = new QListView(this);
    listView = listsong[indexPlaylist];

    try
    {
        QModelIndex index = listView->currentIndex();
        if (!index.isValid() ||!listView)
            throw std::runtime_error("Invalied list view or index");

        QString matchedPlaylistName;
        for (const auto& key : playlistModels.keys())
        {
            if (playlistModels[key] == listView->model())
            {
                matchedPlaylistName = key;
                break;
            }
        }

        if (matchedPlaylistName.isEmpty())
        {
            qDebug() << "Playlist not found for the given QListView";
            return;
        }

        auto& playlist = playlists[matchedPlaylistName];
        if (playlist.empty())
            throw std::runtime_error("Playlist is already empty!");

        int row = index.row();
        if (row < 0 || row >= static_cast<int>(playlist.size()))
            return;

        auto it = playlist.begin();
        std::advance(it, row);

        execute_Command(std::make_unique<RemoveTrackCommand>(
            playlist,
            playlistModels,
            it,
            mainkey[indexPlaylist]
            ));

        if (playlist.empty())
        {
            currentTrack = playlist.end();
            player->stop();
            player->setSource(QString());
            listView->clearSelection();
        }
        else
        {
            if (row < static_cast<int>(playlist.size()))
            {
                currentTrack = playlist.begin();
                std::advance(currentTrack, row);
            }
            else
            {
                currentTrack = std::prev(playlist.end());
            }
            player->setSource(*currentTrack);
        }

        player->pause();
        ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
        ui->label_played->setText("00:00");
        ui->label_remaning->setText("00:00");
        ui->time->setValue(0);

        listView->setModel(playlistModels[matchedPlaylistName]);


    }catch(const std::exception& e)
    {
        qDebug() << "Error in removing track:" <<e.what();
    }
}



void musicplayerpage::on_pushButton_mute_clicked()
{
    muted = !muted;
    if (muted)
    {
        previousVolume = audioOutput->volume() * 100;
        audioOutput->setVolume(0);
        ui->volum->setValue(0);
        ui->pushButton_mute->setIcon(QIcon(":/icons/image/mute.png"));
    }
    else
    {
        audioOutput->setVolume(previousVolume / 100.0);
        ui->volum->setValue(previousVolume);
        ui->pushButton_mute->setIcon(QIcon(":/icons/image/unmute.png"));
    }

}

void musicplayerpage::on_pushButton_shufle_clicked()
{
    execute_Command(std::make_unique<ToggleShuffleCommand>(
        shuffleMode,
        playlists[currentPlaylistName],
        currentTrack,
        shuffledIndices,
        shuffleIndex
        ));

    if (shuffleMode)
    {
        ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle.png"));
    }
    else
    {
        ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle-off.png"));
    }
}

void musicplayerpage::setvolum(int value)
{
    if(value == 0)
    {
        muted = true;
        ui->pushButton_mute->setIcon(QIcon(":/icons/image/mute.png"));
    }
    else
    {
        muted = false;
        ui->pushButton_mute->setIcon(QIcon(":/icons/image/unmute.png"));
    }

     audioOutput->setVolume(value / 100.0f);
}

void musicplayerpage::loadCoverOfMusic()
{
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
