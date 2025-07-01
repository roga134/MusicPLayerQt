#include "myudpclient.h"
#include "musicplayerpage.h"

MyTcpClient::MyTcpClient(QObject *parent)
    : QObject(parent), tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MyTcpClient::onReadyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &MyTcpClient::onDisconnected);
}

void MyTcpClient::connectToServer(const QHostAddress &host, quint16 port)
{
    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, [this]()
    {
        tcpSocket->write(musicplayerpagePtr->GetUserName().toUtf8());
    });
}

void MyTcpClient::sendMessage(const QString &message)
{
    if(message == "pause" || message == "play")
    {
        tcpSocket->write(message.toUtf8());
        return ;
    }

    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        tcpSocket->write(message.toUtf8());
        emit logMessage(QString("Sent: %1").arg(message));
    }
    else
    {
        emit logMessage("Cannot send: not connected to server.");
    }
}

void MyTcpClient::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QString msg = QString::fromUtf8(data).trimmed();

    if (msg == "pause" || msg == "play")
    {
        emit playMusicRequestedclient();
    }

    if (serveruser.isEmpty())
    {
        if (msg.startsWith("admin:")) {
            serveruser = msg.mid(QString("admin:").length());
            emit logMessage("Server admin username set to: " + serveruser);
        } else {
            serveruser = msg;
            emit logMessage("Server username set to: " + serveruser);
        }
        return;
    }

    if (msg.startsWith("userlist:"))
    {
        QStringList userList = msg.mid(QString("userlist:").length()).split("|");

        currusers = userList;
        emit updateDeviceList(userList);
        return;
    }


    int sepIndex = msg.indexOf(": ");
    if (sepIndex != -1) {
        QString sender = msg.left(sepIndex);
        QString message = msg.mid(sepIndex + 2);

        emit logMessage(sender + ": " + message);
        emit messageReceived(message, sender);
    }
    else
    {
        emit logMessage(msg);
        emit messageReceived(msg, serveruser);
    }
}


void MyTcpClient::onDisconnected()
{
    emit logMessage("Disconnected from server.");
}

void MyTcpClient::setMusicPlayerPage(musicplayerpage *page)
{
    try {
        if (!page) {
            throw std::runtime_error("Null pointer passed to setMusicPlayerPage");
        }
        musicplayerpagePtr = page;
    } catch (const std::exception &e) {
        emit logMessage(QString("Error setting music player page: %1").arg(e.what()));
    } catch (...) {
        emit logMessage("Unknown error setting music player page");
    }
}
