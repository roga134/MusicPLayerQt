#include "musicplayer_commands.h"
#include "musicplayerqueue.h"

// PlayCommand class
PlayCommand::PlayCommand(QMediaPlayer* player, std::list<QUrl>::iterator track)
    : player(player) , track(track) {}

void PlayCommand::execute()
{
    if(player->playbackState() == QMediaPlayer::PausedState)
    {
        player->play();
    }
    else
    {
        qDebug() << "Playing track:" << track->toString();
        player->setSource(*track);
        player->play();
    }
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

// AddTrackCommand class
AddTrackCommand::AddTrackCommand(std::list<QUrl>& playlist, QMap<QString, QStandardItemModel*>& model, const QUrl& track, QString key)
    : playlist(playlist), model(model), track(track) , key(key) {}

std::list<QUrl>::iterator AddTrackCommand::executeWithResult()
{
    playlist.push_back(track);
    QStandardItem* item = new QStandardItem(track.fileName());
    item->setData(track.toString(), Qt::UserRole);

    if (!model.contains(key)) {
        qWarning() << "Key not found:" << key;
        return std::prev(playlist.end());
    }

    if (model[key] == nullptr) {
        qWarning() << "Model pointer is nullptr for key:" << key;
        return std::prev(playlist.end());
    }
    model[key]->appendRow(item);
    qDebug() << "Track added:" << track;
    return std::prev(playlist.end());
}

void AddTrackCommand::undo()
{
    if (!playlist.empty()) {
        playlist.pop_back();
        //model->removeRow(model->rowCount() - 1);
    }
}

QString AddTrackCommand::description() const
{
    return "Add: " + track.fileName();
}


// RemoveTrack class
RemoveTrackCommand::RemoveTrackCommand(std::list<QUrl>& playlist, QMap<QString, QStandardItemModel*>& model, std::list<QUrl>::iterator track , QString key)
    : playlist(playlist), model(model), track(track), pos(std::distance(playlist.begin(), track)) , key(key){}


void RemoveTrackCommand::execute()
{
    if (track != playlist.end())
    {
        playlist.erase(track);

        if (model.contains(key))
        {
            QStandardItemModel* playlistModel = model[key];
            if (playlistModel && pos >= 0 && pos < playlistModel->rowCount())
            {
                playlistModel->removeRow(pos);
            }
        }
        else
        {
            qWarning() << "Playlist key not found:" << key;
        }
    }
}

void RemoveTrackCommand::undo()
{
    auto it = playlist.begin();
    std::advance(it, pos);
    playlist.insert(it, *track);

    QStandardItem* item = new QStandardItem(track->fileName());
    item->setData(track->toString(), Qt::UserRole);
    //model->insertRow(pos, item);

}

QString RemoveTrackCommand::description() const
{
    return "Remove: " + track->fileName();
}


//NextTrackcommand class
NextTrackCommand::NextTrackCommand(QMediaPlayer* player, std::list<QUrl>& playlist, std::list<QUrl>::iterator& currentTrack,
                                   QMap<QString, QStandardItemModel*> model, RepeatMode repeatMode, bool shuffle,
                                   MusicPlayerQueue& queue)
    : player(player), playlist(playlist), currentTrack(currentTrack), model(model),
    repeatMode(repeatMode), shuffle(shuffle), queue(queue), originalTrack(currentTrack) {}

void NextTrackCommand::execute()
{
    if (playlist.empty()) return;

    originalTrack = currentTrack;

    if (shuffle)
    {
        int currentPos = std::distance(playlist.begin(), currentTrack);

        if (queue.empty()) {
            queue.initialize(playlist);
        }

        bool moved = queue.moveToNext(currentPos);

        if (!moved)
        {
            if (repeatMode == RepeatMode::RepeatAll)
            {
                queue.initialize(playlist);
                moved = queue.moveToNext(currentPos);
                if (!moved)
                    return;
            }
            else
            {
                return;
            }
        }

        auto it = playlist.begin();
        std::advance(it, currentPos);
        currentTrack = it;
    }
    else
    {
        ++currentTrack;

        if (currentTrack == playlist.end())
        {
            if (repeatMode == RepeatMode::RepeatAll)
            {
                currentTrack = playlist.begin();
            }
            else
            {
                --currentTrack;
                return;
            }
        }
    }

    if (player && currentTrack != playlist.end())
    {
        player->stop();
        player->setSource(*currentTrack);
        player->play();
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

PreviousTrackCommand::PreviousTrackCommand(QMediaPlayer* player, std::list<QUrl>& playlist, std::list<QUrl>::iterator& currentTrack,
                                           QMap<QString, QStandardItemModel*> model, RepeatMode repeatMode, bool shuffle,
                                           MusicPlayerQueue& queue)
    : player(player), playlist(playlist), currentTrack(currentTrack), model(model),
    repeatMode(repeatMode), shuffle(shuffle), queue(queue), originalTrack(currentTrack) {}

void PreviousTrackCommand::execute()
{
    if (playlist.empty())
        return;

    originalTrack = currentTrack;

    int currentPos = std::distance(playlist.begin(), currentTrack);

    if (shuffle)
    {
        if (queue.historyEmpty())
            queue.initialize(playlist);

        bool moved = queue.moveToPrevious(currentPos);

        if (!moved)
        {
            if (repeatMode == RepeatMode::RepeatAll)
            {
                queue.initialize(playlist);
                moved = queue.moveToPrevious(currentPos);
                if (!moved)
                    return;
            }
            else
            {
                return;
            }
        }

        auto it = playlist.begin();
        std::advance(it, currentPos);
        currentTrack = it;
    }
    else
    {
        if (currentTrack == playlist.begin())
        {
            if (repeatMode == RepeatMode::RepeatAll)
            {
                currentTrack = playlist.end();
                --currentTrack;
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
        player->stop();
        player->setSource(*currentTrack);
        player->play();
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
                                           std::list<QUrl>::iterator& currentTrack,
                                           std::vector<int>& shuffledIndices, int& shuffleIndex)
    : shuffleEnabled(shuffleEnabled), playlist(playlist), currentTrack(currentTrack),
    originalTrack(currentTrack), shuffledIndices(shuffledIndices), shuffleIndex(shuffleIndex) {}

void ToggleShuffleCommand::execute()
{
    shuffleEnabled = !shuffleEnabled;

    if (shuffleEnabled)
    {
        shuffledIndices.resize(playlist.size());
        std::iota(shuffledIndices.begin(), shuffledIndices.end(), 0);
        std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), std::mt19937{std::random_device{}()});

        int currentPos = std::distance(playlist.begin(), currentTrack);
        auto it = std::find(shuffledIndices.begin(), shuffledIndices.end(), currentPos);
        if (it != shuffledIndices.end())
        {
            shuffleIndex = std::distance(shuffledIndices.begin(), it);
        }
        else
        {
            shuffleIndex = 0;
        }
    }
    else
    {
        shuffledIndices.clear();
        shuffleIndex = 0;
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
























