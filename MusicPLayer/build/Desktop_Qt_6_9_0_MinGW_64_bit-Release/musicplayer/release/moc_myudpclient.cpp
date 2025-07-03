/****************************************************************************
** Meta object code from reading C++ file 'myudpclient.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../musicplayer/myudpclient.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myudpclient.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11MyTcpClientE_t {};
} // unnamed namespace

template <> constexpr inline auto MyTcpClient::qt_create_metaobjectdata<qt_meta_tag_ZN11MyTcpClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MyTcpClient",
        "updateDeviceList",
        "",
        "userList",
        "logMessage",
        "msg",
        "playMusicRequestedclient",
        "messageReceived",
        "message",
        "sender",
        "adminNameReceived",
        "adminName",
        "playSpecificSongRequested",
        "QString&",
        "songname",
        "onReadyRead",
        "onDisconnected"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'updateDeviceList'
        QtMocHelpers::SignalData<void(const QStringList &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 3 },
        }}),
        // Signal 'logMessage'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 5 },
        }}),
        // Signal 'playMusicRequestedclient'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'messageReceived'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 }, { QMetaType::QString, 9 },
        }}),
        // Signal 'adminNameReceived'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Signal 'playSpecificSongRequested'
        QtMocHelpers::SignalData<void(QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDisconnected'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MyTcpClient, qt_meta_tag_ZN11MyTcpClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MyTcpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11MyTcpClientE_t>.metaTypes,
    nullptr
} };

void MyTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MyTcpClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateDeviceList((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 1: _t->logMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->playMusicRequestedclient(); break;
        case 3: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->adminNameReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->playSpecificSongRequested((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1]))); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->onDisconnected(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)(const QStringList & )>(_a, &MyTcpClient::updateDeviceList, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)(const QString & )>(_a, &MyTcpClient::logMessage, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)()>(_a, &MyTcpClient::playMusicRequestedclient, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)(const QString & , const QString & )>(_a, &MyTcpClient::messageReceived, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)(const QString & )>(_a, &MyTcpClient::adminNameReceived, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (MyTcpClient::*)(QString & )>(_a, &MyTcpClient::playSpecificSongRequested, 5))
            return;
    }
}

const QMetaObject *MyTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11MyTcpClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MyTcpClient::updateDeviceList(const QStringList & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void MyTcpClient::logMessage(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void MyTcpClient::playMusicRequestedclient()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyTcpClient::messageReceived(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2);
}

// SIGNAL 4
void MyTcpClient::adminNameReceived(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void MyTcpClient::playSpecificSongRequested(QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
