#include "myudpserver.h"
#include "musicplayerpage.h"

MyTcpServer::MyTcpServer(musicplayerpage *playerPage, QObject *parent)
    : QObject(parent), musicplayerpagePtr(playerPage)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection, this, &MyTcpServer::onNewConnection);
}

bool MyTcpServer::startServer(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        emit logMessage("Server failed to start.");
        return false;
    }

    emit logMessage(QString("Server started on port %1").arg(port));
    return true;
}

void MyTcpServer::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clients.insert(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead, this, [=]() {
        onReadyRead(clientSocket);
    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [=]() {
        clients.remove(clientSocket);
        emit logMessage("Client disconnected.");
    });

    if (musicplayerpagePtr) {
        QString myUsername = musicplayerpagePtr->GetUserName();
        clientSocket->write(myUsername.toUtf8());
    }

    emit logMessage("New client connected.");
}


void MyTcpServer::onReadyRead(QTcpSocket *clientSocket)
{
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    QString message = QString::fromUtf8(data).trimmed();

    if (!clientUsernames.contains(clientSocket)) {
        clientUsernames[clientSocket] = message;
        emit logMessage("New user registered: " + message);
    }
    else
    {
        QString username = clientUsernames[clientSocket];
        emit messageReceived(message, username);

        for (QTcpSocket* otherClient : clients)
        {
            if (otherClient != clientSocket && otherClient->state() == QAbstractSocket::ConnectedState)
            {
                QString forwardMessage = username + ": " + message;
                otherClient->write(forwardMessage.toUtf8());
            }
        }

        if (message == "pause")
        {
            emit playMusicRequested();
        }/*
        else if (message.startsWith("playlist:"))
        {
            QStringList tracks = message.mid(QString("playlist:").length()).split("|");

            // مثال: ثبت لیست آهنگ کلاینت
            emit logMessage("Received playlist from " + username + ": " + tracks.join(", "));
        }*/
    }
}

void MyTcpServer::onDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    clients.remove(clientSocket);
    QString username = clientUsernames.value(clientSocket, "Unknown");
    clientUsernames.remove(clientSocket);

    emit logMessage("Client disconnected: " + username);
    clientSocket->deleteLater();
}

void MyTcpServer::sendToAllClients(const QString &message)
{
    for (QTcpSocket *client : clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(message.toUtf8());
        }
    }
}

void MyTcpServer::sendToClient(QTcpSocket *client, const QString &message)
{
    if (client && client->state() == QAbstractSocket::ConnectedState) {
        client->write(message.toUtf8());
    }
}
