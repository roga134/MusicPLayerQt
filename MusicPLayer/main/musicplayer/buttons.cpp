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

    if (currentTrack == playlists[currentPlaylistName].end()) {
        currentTrack = playlists[currentPlaylistName].begin();
    }


}



void musicplayerpage::on_pushButton_play_clicked()
{
    if(isPlay)
    {
        execute_Command(std::make_unique<PauseCommand>(player));
        isPlay = false;
    }
    else
    {
        if (!playlists[currentPlaylistName].empty())
        {
            if (currentTrack == playlists[currentPlaylistName].end())
            {
                currentTrack = playlists[currentPlaylistName].begin();
            }
            execute_Command(std::make_unique<PlayCommand>(player, currentTrack));
            isPlay = true ;
        }
    }
}


void musicplayerpage::execute_Command(std::unique_ptr<Command> command)
{
    command->execute();
}

void musicplayerpage::on_pushButton_prev_clicked()
{
    execute_Command(std::make_unique<PreviousTrackCommand>(player, playlists[currentPlaylistName], currentTrack, playlistModel, repeatMode, shuffleMode));
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
        shuffleMode));
}

