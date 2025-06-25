// #include "musicplayerpage.h"
// #include "ui_musicplayerpage.h"

// void musicplayerpage::update_playlistUI()
// {
//     playlistModel->removeRows(0, playlistModel->rowCount());

//     for (const auto& track : playlists[currentPlaylistName]) {
//         QStandardItem* item = new QStandardItem(track.fileName());
//         item->setData(track.toString(), Qt::UserRole);
//         playlistModel->appendRow(item);
//     }
// }

// void musicplayerpage::save_playlist_to_file()
// {
//     try
//     {
//         QFile file("playlists.dat");
//         if (file.open(QIODevice::WriteOnly))
//         {
//             QDataStream out(&file);
//             out << static_cast<int>(playlists.size());

//             for (const auto& [name, tracks] : playlists)
//             {
//                 out << name;
//                 out << static_cast<int>(tracks.size());

//                 for (const auto& url : tracks)
//                 {
//                     out << url;
//                 }
//             }
//         }
//     } catch (...)
//     {
//         qWarning() << "Failed to save playlists";
//     }
// }

