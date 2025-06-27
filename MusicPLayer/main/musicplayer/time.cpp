#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_time_sliderMoved(int position)
{
    player->setPosition(position);
    ui->label_played->setText(formatTime(position));
}

 void musicplayerpage::on_positionChanged(qint64 position)
{
    if (!ui->time->isSliderDown()) {
        ui->time->setValue(position);
    }
    ui->label_played->setText(formatTime(position));
}

QString musicplayerpage::formatTime(qint64 milliseconds)
{
    qint64 seconds = milliseconds / 1000;
    qint64 minutes = seconds / 60;
    seconds %= 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void musicplayerpage::on_durationChanged(qint64 duration)
{
    ui->time->setRange(0, duration);
    ui->label_remaning->setText(formatTime(duration));

    // Update duration in playlist
    if (currentTrack != playlists[currentPlaylistName].end()) {
        int row = std::distance(playlists[currentPlaylistName].begin(), currentTrack);
        QStandardItem* durationItem = playlistModels[currentPlaylistName]->item(row, 1);
        if (durationItem) {
            durationItem->setText(formatTime(duration));
        }
    }
}
void musicplayerpage::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        if (repeatMode == RepreatOne)
        {
            player->play();
        }
        else
        {
            on_pushButton_next_clicked();
        }
    }
}
