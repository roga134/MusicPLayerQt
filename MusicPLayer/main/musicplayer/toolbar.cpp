#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_actionprevios_song_triggered()
{
    this->on_pushButton_prev_clicked();
}

void musicplayerpage::on_actionplay_triggered()
{
    this->on_pushButton_play_clicked();
}

void musicplayerpage::on_actionnext_trak_triggered()
{
    this->on_pushButton_next_clicked();
}

void musicplayerpage::on_actionexit_triggered()
{
    QApplication::quit();
}

void musicplayerpage::on_actionDon_t_shuffel_triggered()
{
    shuffleMode = false;

    ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle-off.png"));
}

void musicplayerpage::on_actionshuffel_all_triggered()
{
    shuffleMode = true;

    ui->pushButton_shufle->setIcon(QIcon(":/icons/image/shuffle.png"));
}

void musicplayerpage::on_actionadd_playlist_triggered()
{
    on_pushButton_creatPlaylist_clicked();
}

void musicplayerpage::on_actionsave_playlist_triggered()
{
    on_pushButton_savePlaylist_clicked();
}

void musicplayerpage::on_actionload_playlist_triggered()
{
    on_pushButton_loadPlaylist_clicked();
}
