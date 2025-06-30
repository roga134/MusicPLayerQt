/****************************************************************************
** Meta object code from reading C++ file 'musicplayerpage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../musicplayer/musicplayerpage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicplayerpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15musicplayerpageE_t {};
} // unnamed namespace

template <> constexpr inline auto musicplayerpage::qt_create_metaobjectdata<qt_meta_tag_ZN15musicplayerpageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "musicplayerpage",
        "on_pushButton_play_clicked",
        "",
        "play_pause_network",
        "on_positionChanged",
        "position",
        "on_durationChanged",
        "duration",
        "on_mediaStatusChanged",
        "QMediaPlayer::MediaStatus",
        "status",
        "on_actionAdd_Track_triggered",
        "on_pushButton_prev_clicked",
        "on_pushButton_next_clicked",
        "on_actionRemove_Track_triggered",
        "on_pushButton_mute_clicked",
        "on_volum_valueChanged",
        "value",
        "on_time_sliderMoved",
        "on_pushButton_shufle_clicked",
        "on_pushButton_files_clicked",
        "save_playlist_to_file",
        "QModelIndex",
        "index",
        "on_pushButton_back_clicked",
        "on_actionopen_file_triggered",
        "onItemDoubleClicked",
        "handleDoubleClickFromListView",
        "QListView*",
        "listView",
        "setvolum",
        "on_pushButton_home_clicked",
        "on_pushButton_forward_clicked",
        "on_actionprevios_song_triggered",
        "on_actionplay_triggered",
        "on_actionnext_trak_triggered",
        "on_actionexit_2_triggered",
        "on_actionDon_t_shuffel_triggered",
        "on_actionshuffel_all_triggered",
        "on_actionadd_playlist_triggered",
        "on_actionsave_playlist_triggered",
        "on_actionload_playlist_triggered",
        "on_pushButton_creatPlaylist_clicked",
        "onTabChanged",
        "showContextMenu",
        "pos",
        "addToQueueFromListView",
        "createQueueTab",
        "on_pushButton_savePlaylist_clicked",
        "on_pushButton_loadPlaylist_clicked",
        "renamePlaylistTab",
        "loadCoverOfMusic",
        "on_pushButton_mode3_clicked",
        "ChangeGraphicView",
        "on_pushButton_server_clicked",
        "on_pushButton_client_clicked",
        "on_pushButton_chat_clicked",
        "addChatMessage",
        "message",
        "isMyMessage",
        "on_pushButton_info_clicked",
        "on_actionUndo_triggered",
        "settoolbar",
        "on_actionDon_t_repeat_triggered",
        "on_actionrepeat_trak_triggered",
        "on_actionrepeat_playlist_triggered"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_pushButton_play_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'play_pause_network'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_positionChanged'
        QtMocHelpers::SlotData<void(qint64)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 5 },
        }}),
        // Slot 'on_durationChanged'
        QtMocHelpers::SlotData<void(qint64)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 7 },
        }}),
        // Slot 'on_mediaStatusChanged'
        QtMocHelpers::SlotData<void(QMediaPlayer::MediaStatus)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'on_actionAdd_Track_triggered'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_prev_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_next_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionRemove_Track_triggered'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_mute_clicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_volum_valueChanged'
        QtMocHelpers::SlotData<void(int)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 17 },
        }}),
        // Slot 'on_time_sliderMoved'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'on_pushButton_shufle_clicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_files_clicked'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'save_playlist_to_file'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'on_pushButton_back_clicked'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionopen_file_triggered'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onItemDoubleClicked'
        QtMocHelpers::SlotData<void(const QModelIndex &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'handleDoubleClickFromListView'
        QtMocHelpers::SlotData<void(QListView *, const QModelIndex &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 28, 29 }, { 0x80000000 | 22, 23 },
        }}),
        // Slot 'setvolum'
        QtMocHelpers::SlotData<void(int)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 17 },
        }}),
        // Slot 'on_pushButton_home_clicked'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_forward_clicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionprevios_song_triggered'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionplay_triggered'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionnext_trak_triggered'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionexit_2_triggered'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionDon_t_shuffel_triggered'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionshuffel_all_triggered'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionadd_playlist_triggered'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionsave_playlist_triggered'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionload_playlist_triggered'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_creatPlaylist_clicked'
        QtMocHelpers::SlotData<void()>(42, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTabChanged'
        QtMocHelpers::SlotData<void(int)>(43, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'showContextMenu'
        QtMocHelpers::SlotData<void(const QPoint &)>(44, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QPoint, 45 },
        }}),
        // Slot 'addToQueueFromListView'
        QtMocHelpers::SlotData<void(QListView *, const QModelIndex &)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 28, 29 }, { 0x80000000 | 22, 23 },
        }}),
        // Slot 'createQueueTab'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_savePlaylist_clicked'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_loadPlaylist_clicked'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'renamePlaylistTab'
        QtMocHelpers::SlotData<void(int)>(50, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'loadCoverOfMusic'
        QtMocHelpers::SlotData<void()>(51, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_mode3_clicked'
        QtMocHelpers::SlotData<void()>(52, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'ChangeGraphicView'
        QtMocHelpers::SlotData<void(QPoint)>(53, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QPoint, 45 },
        }}),
        // Slot 'on_pushButton_server_clicked'
        QtMocHelpers::SlotData<void()>(54, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_client_clicked'
        QtMocHelpers::SlotData<void()>(55, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_chat_clicked'
        QtMocHelpers::SlotData<void()>(56, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'addChatMessage'
        QtMocHelpers::SlotData<void(const QString &, bool)>(57, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 58 }, { QMetaType::Bool, 59 },
        }}),
        // Slot 'on_pushButton_info_clicked'
        QtMocHelpers::SlotData<void()>(60, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionUndo_triggered'
        QtMocHelpers::SlotData<void()>(61, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'settoolbar'
        QtMocHelpers::SlotData<void()>(62, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionDon_t_repeat_triggered'
        QtMocHelpers::SlotData<void()>(63, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionrepeat_trak_triggered'
        QtMocHelpers::SlotData<void()>(64, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionrepeat_playlist_triggered'
        QtMocHelpers::SlotData<void()>(65, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<musicplayerpage, qt_meta_tag_ZN15musicplayerpageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject musicplayerpage::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15musicplayerpageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15musicplayerpageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15musicplayerpageE_t>.metaTypes,
    nullptr
} };

void musicplayerpage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<musicplayerpage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_pushButton_play_clicked(); break;
        case 1: _t->play_pause_network(); break;
        case 2: _t->on_positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 3: _t->on_durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 4: _t->on_mediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 5: _t->on_actionAdd_Track_triggered(); break;
        case 6: _t->on_pushButton_prev_clicked(); break;
        case 7: _t->on_pushButton_next_clicked(); break;
        case 8: _t->on_actionRemove_Track_triggered(); break;
        case 9: _t->on_pushButton_mute_clicked(); break;
        case 10: _t->on_volum_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_time_sliderMoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_pushButton_shufle_clicked(); break;
        case 13: _t->on_pushButton_files_clicked(); break;
        case 14: _t->save_playlist_to_file((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 15: _t->on_pushButton_back_clicked(); break;
        case 16: _t->on_actionopen_file_triggered(); break;
        case 17: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 18: _t->handleDoubleClickFromListView((*reinterpret_cast< std::add_pointer_t<QListView*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 19: _t->setvolum((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->on_pushButton_home_clicked(); break;
        case 21: _t->on_pushButton_forward_clicked(); break;
        case 22: _t->on_actionprevios_song_triggered(); break;
        case 23: _t->on_actionplay_triggered(); break;
        case 24: _t->on_actionnext_trak_triggered(); break;
        case 25: _t->on_actionexit_2_triggered(); break;
        case 26: _t->on_actionDon_t_shuffel_triggered(); break;
        case 27: _t->on_actionshuffel_all_triggered(); break;
        case 28: _t->on_actionadd_playlist_triggered(); break;
        case 29: _t->on_actionsave_playlist_triggered(); break;
        case 30: _t->on_actionload_playlist_triggered(); break;
        case 31: _t->on_pushButton_creatPlaylist_clicked(); break;
        case 32: _t->onTabChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 33: _t->showContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 34: _t->addToQueueFromListView((*reinterpret_cast< std::add_pointer_t<QListView*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 35: _t->createQueueTab(); break;
        case 36: _t->on_pushButton_savePlaylist_clicked(); break;
        case 37: _t->on_pushButton_loadPlaylist_clicked(); break;
        case 38: _t->renamePlaylistTab((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 39: _t->loadCoverOfMusic(); break;
        case 40: _t->on_pushButton_mode3_clicked(); break;
        case 41: _t->ChangeGraphicView((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 42: _t->on_pushButton_server_clicked(); break;
        case 43: _t->on_pushButton_client_clicked(); break;
        case 44: _t->on_pushButton_chat_clicked(); break;
        case 45: _t->addChatMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 46: _t->on_pushButton_info_clicked(); break;
        case 47: _t->on_actionUndo_triggered(); break;
        case 48: _t->settoolbar(); break;
        case 49: _t->on_actionDon_t_repeat_triggered(); break;
        case 50: _t->on_actionrepeat_trak_triggered(); break;
        case 51: _t->on_actionrepeat_playlist_triggered(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListView* >(); break;
            }
            break;
        case 34:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QListView* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *musicplayerpage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *musicplayerpage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15musicplayerpageE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int musicplayerpage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    }
    return _id;
}
QT_WARNING_POP
