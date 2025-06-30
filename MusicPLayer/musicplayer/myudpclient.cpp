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
    emit logMessage(QString("Connecting to %1:%2 ...").arg(host.toString()).arg(port));

    connect(tcpSocket, &QTcpSocket::connected, this, [=]() {
        emit logMessage("Connected to server.");
        if (musicplayerpagePtr)
        {
            QString myUsername = musicplayerpagePtr->GetUserName();
            tcpSocket->write(myUsername.toUtf8());
        }
    });
}

void MyTcpClient::sendMessage(const QString &message)
{
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

    if (serveruser.isEmpty())
    {
        serveruser = msg;
        emit logMessage("Server username set to: " + serveruser);
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

        if (msg == "pause")
        {
            emit playMusicRequestedclient();
        }
        else if (msg.startsWith("playlist:"))
        {
            QStringList serverTracks = msg.mid(QString("playlist:").length()).split("|");
            QStringList clientTracks = musicplayerpagePtr->getAllTrackNames();

            for (const QString &track : clientTracks)
            {
                if (!serverTracks.contains(track))
                {
                    emit logMessage("Track missing on server: " + track);
                }
            }

            for (const QString &track : serverTracks)
            {
                if (!clientTracks.contains(track))
                {
                    emit logMessage("Track missing on client: " + track);
                }
            }
        }
    }
}

void MyTcpClient::onDisconnected()
{
    emit logMessage("Disconnected from server.");
}

void MyTcpClient::setMusicPlayerPage(musicplayerpage *page)
{
    musicplayerpagePtr = page;
    try{
        if(!page)
        {
            throw std::runtime_error("Null pointer passed to setMusicPlayerPage");
        }
        musicplayerpagePtr = page;
    }catch(const std::exception &e)
    {
        emit logMessage("Error setting music player page");
    }
    catch(...)
    {
        emit logMessage("Unknow error setting music player page");

    }
}
