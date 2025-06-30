#include "myudpserver.h"
#include "musicplayerpage.h"

MyTcpServer::MyTcpServer(musicplayerpage *playerPage, QObject *parent)
    : QObject(parent), musicplayerpagePtr(playerPage)
{}

bool MyTcpServer::startServer(quint16 port)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &MyTcpServer::onNewConnection);
    bool listening = tcpServer->listen(QHostAddress::AnyIPv4, port);
    if (listening)
        emit logMessage(QString("TCP Server started on port %1").arg(port));
    else
        emit logMessage(QString("Failed to start TCP Server: %1").arg(tcpServer->errorString()));
    return listening;
}

void MyTcpServer::onNewConnection()
{
    while (tcpServer->hasPendingConnections())
    {
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
        clients.insert(clientSocket);

        connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
            onReadyRead(clientSocket);
        });

        connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
            clients.remove(clientSocket);
            playlistSent.remove(clientSocket);
            clientSocket->deleteLater();
            emit logMessage("Client disconnected");
        });

        emit logMessage("New client connected: " + clientSocket->peerAddress().toString());
    }
}


void MyTcpServer::onReadyRead(QTcpSocket *clientSocket)
{
    QByteArray data = clientSocket->readAll();
    QString msg = QString::fromUtf8(data).trimmed();

    emit logMessage("Received from client: " + msg);
    emit messageReceived(msg, clientSocket->peerAddress().toString());

    if (msg == "pause")
    {
        emit playMusicRequested();
    }
    else if (msg.startsWith("playlist:"))
    {
        if (!playlistSent.value(clientSocket, false))
        {

            QStringList clientTracks = msg.mid(QString("playlist:").length()).split("|");
            QStringList serverTracks;

            if (musicplayerpagePtr)
            {
                serverTracks = musicplayerpagePtr->getAllTrackNames();
            }
            else
            {
                emit logMessage("Error: musicplayerpagePtr is null. Cannot retrieve server tracks.");
                return;
            }


            QString joined = serverTracks.join("|");
            QString response = "playlist:" + joined;
            clientSocket->write(response.toUtf8());

            playlistSent[clientSocket] = true;

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
        else
        {
            emit logMessage("Playlist already sent to this client, skipping response.");
        }
    }
}



void MyTcpServer::sendToAllClients(const QString &message)
{
    QByteArray data = message.toUtf8();
    for (QTcpSocket *client : std::as_const(clients))
    {
        client->write(data);
    }
    emit logMessage("Sent to all clients: " + message);
}

void MyTcpServer::sendToClient(const QHostAddress &address, quint16 port, const QString &message)
{
    for (QTcpSocket *client : std::as_const(clients))
    {
        if (client->peerAddress() == address && client->peerPort() == port)
        {
            client->write(message.toUtf8());
            emit logMessage(QString("Sent to %1:%2 - %3").arg(address.toString()).arg(port).arg(message));
            break;
        }
    }
}
