#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionAdd_Track_triggered()
{
    QUrl trackUrl = QFileDialog::getOpenFileUrl(this, "Select Audio File", QUrl::fromLocalFile(QDir::homePath()),  "(*.*) All Files");

    if (!trackUrl.isValid() || trackUrl.isEmpty())
    {
        qDebug() << "No file selected";
        return;
    }
    if(!QFile::exists(trackUrl.toLocalFile()))
    {
        qDebug() << "File dose not exist" << trackUrl.toLocalFile();
        return ;
    }
    execute_Command(std::make_unique<AddTrackCommand>(
        playlists[currentPlaylistName],
        playlistModel,
        trackUrl
        ));

    if (currentTrack == playlists[currentPlaylistName].end())
    {
        currentTrack = playlists[currentPlaylistName].begin();
    }
}

void musicplayerpage::on_pushButton_play_clicked()
{
    if (player->playbackState() == QMediaPlayer::PlayingState)
    {
        execute_Command(std::make_unique<PauseCommand>(player));
        ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
    }
    else
    {
        if (!playlists[currentPlaylistName].empty())
        {
            if (currentTrack == playlists[currentPlaylistName].end())
                currentTrack = playlists[currentPlaylistName].begin();

            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            lastTrack = currentTrack;
            ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));
        }
    }
}

void musicplayerpage::onItemDoubleClicked(const QModelIndex &index)
{
    auto &playlist = playlists[currentPlaylistName];
    int row = index.row();

    auto it = playlist.begin();
    std::advance(it, row);
    currentTrack = it;

    execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
    lastTrack = currentTrack;
    ui->pushButton_play->setIcon(QIcon(":/icons/image/pause.png"));
}

void musicplayerpage::execute_Command(std::unique_ptr<Command> command)
{
    command->execute();
}

void musicplayerpage::on_pushButton_prev_clicked()
{
    execute_Command(std::make_unique<PreviousTrackCommand>(
        player,
        playlists[currentPlaylistName],
        currentTrack,
        playlistModel,
        repeatMode,
        shuffleMode,
        shuffledIndices,
        shuffleIndex
        ));

    int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
    ui->listSongs->setCurrentIndex(playlistModel->index(row, 0));
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
                        playlistModel,
                        repeatMode,
                        shuffleMode,
                        shuffledIndices,
                        shuffleIndex
    ));

    int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
    ui->listSongs->setCurrentIndex(playlistModel->index(row, 0));
}

void musicplayerpage::on_actionRemove_Track_triggered()
{
        if (playlists[currentPlaylistName].empty() || currentTrack == playlists[currentPlaylistName].end())
            return;

        int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
        execute_Command(std::make_unique<RemoveTrackCommand>(
            playlists[currentPlaylistName],
            playlistModel,
            currentTrack
            ));


        if (playlists[currentPlaylistName].empty())
        {
            currentTrack = playlists[currentPlaylistName].end();
        }
        else
        {
            currentTrack = playlists[currentPlaylistName].begin();
        }

        execute_Command(std::make_unique<PauseCommand>(player));
        ui->pushButton_play->setIcon(QIcon(":/icons/image/play-buttton.png"));
        ui->label_played->setText("00:00");
        ui->label_remaning->setText("00:00");
        ui->time->setValue(0);
        currentTrack = playlists[currentPlaylistName].begin();////////////////////////اینجا باگ داره که اون اهنگی که حذف میشه بازم دکمه پلی رو بزنه اجرا میشه
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
