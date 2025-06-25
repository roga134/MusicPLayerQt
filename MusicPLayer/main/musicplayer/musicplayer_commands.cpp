#include "musicplayer_commands.h"

// PlayCommand class
PlayCommand::PlayCommand(QMediaPlayer* player, std::list<QUrl>::iterator track)
    : player(player), track(track) {}

void PlayCommand::execute()
{
        player->setSource(*track);
        player->play();
}

void PlayCommand::undo()
{
    if (player)
    {
        player->pause();
    }
}

QString PlayCommand::description() const
{
    return  "Play: " + track->fileName();
}


// PauseCommand class
PauseCommand::PauseCommand(QMediaPlayer* player) : player(player) {}

void PauseCommand::execute()
{
    if (player)
    {
        player->pause();
    }
}

void PauseCommand::undo()
{
    if (player)
    {
        player->play();
    }
}

QString PauseCommand::description() const
{
    return "Pause";
}


// StopCommand class
StopCommand::StopCommand(QMediaPlayer* player) : player(player) {}

void StopCommand::execute()
{
    if (player)
    {
        player->stop();
    }
}

void StopCommand::undo()
{
    if (player)
    {
        player->play();
    }
}

QString StopCommand::description() const
{
    return "Stop";
}


// AddTrackCommand class
AddTrackCommand::AddTrackCommand(std::list<QUrl>& playlist, QStandardItemModel* model, const QUrl& track)
    : playlist(playlist), model(model), track(track) {}

void AddTrackCommand::execute()
{
    playlist.push_back(track);
    QStandardItem* item = new QStandardItem(track.fileName());
    item->setData(track.toString(), Qt::UserRole);
    model->appendRow(item);

    qDebug() << "Track added :"<< track ;
}

void AddTrackCommand::undo()
{
    if (!playlist.empty()) {
        playlist.pop_back();
        model->removeRow(model->rowCount() - 1);
    }
}

QString AddTrackCommand::description() const
{
    return "Add: " + track.fileName();
}


// RemoveTrack class
RemoveTrackCommand::RemoveTrackCommand(std::list<QUrl>& playlist, QStandardItemModel* model, std::list<QUrl>::iterator track)
    : playlist(playlist), model(model), track(track), pos(std::distance(playlist.begin(), track)) {}

void RemoveTrackCommand::execute()
{
    if (track != playlist.end())
    {
        playlist.erase(track);
        model->removeRow(pos);
    }
}

void RemoveTrackCommand::undo()
{
    auto it = playlist.begin();
    std::advance(it, pos);
    playlist.insert(it, *track);

    QStandardItem* item = new QStandardItem(track->fileName());
    item->setData(track->toString(), Qt::UserRole);
    model->insertRow(pos, item);

}

QString RemoveTrackCommand::description() const
{
    return "Remove: " + track->fileName();
}


//NextTrackcommand class
NextTrackCommand::NextTrackCommand(QMediaPlayer* player, std::list<QUrl>&playlist, std::list<QUrl>::iterator& currentTrack,
                 QStandardItemModel* model, RepeatMode repeatMode, bool shuffle)
    : player(player), playlist(playlist), currentTrack(currentTrack), model(model),
    repeatMode(repeatMode), shuffle(shuffle), originalTrack(currentTrack) {}

void NextTrackCommand::execute()
{
    if (playlist.empty()) return;

    // Save original state for undo
    originalTrack = currentTrack;

    if (shuffle) {
        // Initialize shuffled indices if empty
        if (shuffledIndices.empty()) {
            shuffledIndices.resize(playlist.size());
            std::iota(shuffledIndices.begin(), shuffledIndices.end(), 0);
            std::random_shuffle(shuffledIndices.begin(), shuffledIndices.end());
        }

        shuffleIndex = (shuffleIndex + 1) % shuffledIndices.size();
        currentTrack = playlist.begin();
        std::advance(currentTrack, shuffledIndices[shuffleIndex]);
    }
    else {
        ++currentTrack;

        if (currentTrack == playlist.end()) {
            if (repeatMode == RepeatMode::RepeatAll) {
                currentTrack = playlist.begin();
            } else {
                currentTrack = originalTrack; // Revert
                return;
            }
        }
    }

    if (player) {
        player->stop();
        player->setSource(*currentTrack);
        player->play();

        // Update UI
        //int row = std::distance(playlist.begin(), currentTrack);
       // QModelIndex index = model->index(row, 0);
       // emit model->dataChanged(index, index, {Qt::BackgroundRole});
    }
}

void NextTrackCommand::undo()
{
    currentTrack = originalTrack;
    if (player && currentTrack != playlist.end())
    {
        player->setSource(*currentTrack);
        player->play();
    }
}

QString NextTrackCommand::description() const
{
    return "Next Track";
}


// PreviousCommand class

PreviousTrackCommand::PreviousTrackCommand(QMediaPlayer* player, std::list<QUrl> playlist, std::list<QUrl>::iterator& currentTrack,
                     QStandardItemModel* model, RepeatMode repeatMode, bool shuffle)
    : player(player), playlist(playlist), currentTrack(currentTrack), model(model),
    repeatMode(repeatMode), shuffle(shuffle), originalTrack(currentTrack) {}

void PreviousTrackCommand::execute()
{
    if (playlist.empty())
    {
        return;
    }

    if (shuffle && !shuffledIndices.empty())
    {
        shuffleIndex = (shuffleIndex - 1 + shuffledIndices.size()) % shuffledIndices.size();
        auto it = playlist.begin();
        std::advance(it, shuffledIndices[shuffleIndex]);
        currentTrack = it;
    }
    else
    {
        if (currentTrack == playlist.begin())
        {
            if (repeatMode == RepeatMode::RepeatAll)
            {
                currentTrack = --playlist.end();
            }
            else
            {
                return;
            }
        }
        else
        {
            --currentTrack;
        }
    }

    if (player && currentTrack != playlist.end())
    {
        player->setSource(*currentTrack);
        player->play();

        // int row = std::distance(playlist.begin(), currentTrack);
        // QModelIndex index = model->index(row, 0);
        // emit model->dataChanged(index, index, {Qt::BackgroundRole});
    }
}

void PreviousTrackCommand::undo()
{
    currentTrack = originalTrack;
    if (player && currentTrack != playlist.end())
    {
        player->setSource(*currentTrack);
        player->play();
    }
}

QString PreviousTrackCommand::description() const
{
    return "Previous Track";
}


//SetValume class
SetVolumeCommand::SetVolumeCommand(QAudioOutput* audioOutput, int newVolume, int oldVolume)
    : audioOutput(audioOutput), newVolume(newVolume), oldVolume(oldVolume) {}

void SetVolumeCommand::execute()
{
    if (audioOutput)
    {
        audioOutput->setVolume(newVolume / 100.0f);
    }
}

void SetVolumeCommand::undo()
{
    if (audioOutput) {
        audioOutput->setVolume(oldVolume / 100.0f);
    }
}

QString SetVolumeCommand::description() const
{
    return QString("Set Volume: %1%").arg(newVolume);
}


// SeekCommand class

SeekCommand::SeekCommand(QMediaPlayer* player, qint64 newPosition, qint64 oldPosition)
    : player(player), newPosition(newPosition), oldPosition(oldPosition) {}

void SeekCommand::execute()
{
    if (player) {
        player->setPosition(newPosition);
    }
}

void SeekCommand::undo()
{
    if (player) {
        player->setPosition(oldPosition);
    }
}

QString SeekCommand::description() const
{
    return QString("Seek to %1").arg(newPosition);
}


// createPlayList class
CreatePlaylistCommand::CreatePlaylistCommand(QMap<QString, std::list<QUrl>>& playlists,
                      QStringListModel* playlistsModel, const QString& name)
    : playlists(playlists), playlistsModel(playlistsModel), name(name) {}

void CreatePlaylistCommand::execute()
{
    if (!playlists.contains(name))
    {
        playlists.insert(name, std::list<QUrl>());

        QStringList list = playlistsModel->stringList();
        list.append(name);
        playlistsModel->setStringList(list);
    }
}

void CreatePlaylistCommand::undo()
{
    if (playlists.contains(name))
    {
        playlists.remove(name);
        QStringList list = playlistsModel->stringList();
        list.removeAll(name);
        playlistsModel->setStringList(list);
    }
}

QString CreatePlaylistCommand::description() const
{
    return "Create Playlist: " + name;
}


// DeletePlayListCommand class

DeletePlaylistCommand::DeletePlaylistCommand(QMap<QString, std::list<QUrl>>& playlists,QStringListModel* playlistsModel, const QString& name)
    : playlists(playlists), playlistsModel(playlistsModel), name(name),
    playlistContent(playlists.value(name)) {}

void DeletePlaylistCommand::execute()
{
    if (playlists.contains(name))
    {
        playlists.remove(name);

        QStringList list = playlistsModel->stringList();
        list.removeAll(name);
        playlistsModel->setStringList(list);
    }
}

void DeletePlaylistCommand::undo()
{
    if (!playlists.contains(name))
    {
        playlists.insert(name, playlistContent);
        QStringList list = playlistsModel->stringList();
        list.append(name);
        playlistsModel->setStringList(list);
    }
}

QString DeletePlaylistCommand::description() const
{
    return "Delete Playlist: " + name;
}


// SetRepeatModel class

SetRepeatModeCommand::SetRepeatModeCommand(RepeatMode& currentMode, RepeatMode newMode)
    : currentMode(currentMode), newMode(newMode), oldMode(currentMode) {}

void SetRepeatModeCommand::execute()
{
    currentMode = newMode;
}

void SetRepeatModeCommand::undo()
{
    currentMode = oldMode;
}

QString SetRepeatModeCommand::description() const
{
    return QString("Set Repeat Mode: %1").arg(static_cast<int>(newMode));
}


// ToggleShuffleCommand  class
ToggleShuffleCommand::ToggleShuffleCommand(bool& shuffleEnabled, std::list<QUrl>& playlist,
                     std::list<QUrl>::iterator& currentTrack)
    : shuffleEnabled(shuffleEnabled), playlist(playlist),
    currentTrack(currentTrack), originalTrack(currentTrack) {}

void ToggleShuffleCommand::execute()
{
    shuffleEnabled = !shuffleEnabled;

    if (shuffleEnabled)
    {
        // Generate shuffled indices
        shuffledIndices.resize(playlist.size());
        std::iota(shuffledIndices.begin(), shuffledIndices.end(), 0);
        std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), std::mt19937{std::random_device{}()});

        // Find current track in shuffled order
        int currentPos = std::distance(playlist.begin(), currentTrack);
        auto it = std::find(shuffledIndices.begin(), shuffledIndices.end(), currentPos);
        if (it != shuffledIndices.end())
        {
            shuffleIndex = std::distance(shuffledIndices.begin(), it);
        }
    }
}

void ToggleShuffleCommand::undo()
{
    shuffleEnabled = !shuffleEnabled;
    currentTrack = originalTrack;
}

QString ToggleShuffleCommand::description() const
{
    return QString("Toggle Shuffle: %1").arg(shuffleEnabled ? "On" : "Off");
}
























