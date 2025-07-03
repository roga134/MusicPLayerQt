#include "myudpserver.h"
#include "musicplayerpage.h"

MyTcpServer::MyTcpServer(musicplayerpage *playerPage, QObject *parent)
    : QObject(parent), musicplayerpagePtr(playerPage)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &MyTcpServer::onNewConnection);
    connect(musicplayerpagePtr, &musicplayerpage::requestUserRemoval, this, &MyTcpServer::removeUserByUsername);
}

bool MyTcpServer::startServer(quint16 port)
{
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        emit logMessage("Server failed to start.");
        return false;
    }

    emit logMessage(QString("Server started on port %1").arg(port));

    if (musicplayerpagePtr) {
        adminUsername = musicplayerpagePtr->GetUserName();
    }

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
        onDisconnected();
    });

    emit logMessage("New client connected.");

    if (!adminUsername.isEmpty() && !initializedClients.contains(clientSocket))
    {
        clientSocket->write(("admin:" + adminUsername + "\n").toUtf8());
        initializedClients.insert(clientSocket);
    }
}

void MyTcpServer::onReadyRead(QTcpSocket *clientSocket)
{
    if (!clientSocket)
        return;

    QByteArray data = clientSocket->readAll();
    QString message = QString::fromUtf8(data).trimmed();

    if (message.isEmpty())
        return;

    if (!clientUsernames.contains(clientSocket))
    {
        clientUsernames[clientSocket] = message;
        emit logMessage("New user registered: " + message);\
            emit messageReceived("connected",message);
        QTimer::singleShot(100,this,[this]()
        {

        broadcastUserList();
            });
        return;
    }


    QString username = clientUsernames.value(clientSocket);

    if (message.startsWith("inplay:"))
    {
        QString songName = message.mid(QString("inplay:").length());

        emit playSpecificSongRequested(songName);
        forwardCommandToOthers(clientSocket , message);
        return;
    }

    if(message == "mission file")
    {
        QFile file(musicplayerpagePtr->getfilesong());

        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot open file for reading!";
            return;
        }

        QByteArray fileData = file.readAll();
        file.close();  // بهتره بعد از readAll

        QString fileName = QFileInfo(file).fileName();
        QByteArray header = "FILE:" + fileName.toUtf8() + ":" + QByteArray::number(fileData.size()) + "\n";

        qDebug() << "Sending file:" << fileName << "Size:" << fileData.size();

        for (QTcpSocket* client : clients)
        {
            client->write(header);
            client->write(fileData);
            client->flush();
        }
    }

    if (message == "request_user_list")
    {
        QStringList usernames = getAllUsernames();
        if (!adminUsername.isEmpty() && !usernames.contains(adminUsername))
            usernames.append(adminUsername);
        QString userListMsg = "userlist:" + usernames.join("|") + "\n";
        clientSocket->write(userListMsg.toUtf8());
        return;
    }

    int sepIndex = message.indexOf(": ");
    if(message.contains(": "))
    {   
        QString sender = message.left(sepIndex);
        QString msgBody = message.mid(sepIndex + 2);
        emit logMessage(sender + ": " + msgBody);
        emit messageReceived(msgBody , sender);
    }
    else 
    {
        QString sender = clientUsernames.value(clientSocket , "Unkonw");
        emit logMessage(sender + ": " + message);
        emit messageReceived(message , sender);
    }

    QString forwardMessage = username + ": " + message + "\n";
    for (QTcpSocket* otherClient : clients)
    {
        if (otherClient != clientSocket && otherClient->state() == QAbstractSocket::ConnectedState)
        {
            otherClient->write(forwardMessage.toUtf8());
        }
    }
}

void MyTcpServer::forwardCommandToOthers(QTcpSocket* sender, const QString& command)
{
    for (QTcpSocket* client : clients) {
        if (client != sender && client->state() == QAbstractSocket::ConnectedState) {
            client->write(command.toUtf8());
        }
    }
}


void MyTcpServer::onDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket)
        return;

    QString username = clientUsernames.take(clientSocket);
    clients.remove(clientSocket);
    initializedClients.remove(clientSocket);

    emit logMessage("Client disconnected: " + username);
    emit messageReceived("disconnected" , username);
    sendToAllClients("disconnected(" + username+")\n");
    QTimer::singleShot(100 , this , [this]()
    {
        broadcastUserList();
    });
    clientSocket->deleteLater();
}

void MyTcpServer::sendToAllClients(const QString &message)
{
    for (QTcpSocket *client : clients)
    {
        if (client->state() == QAbstractSocket::ConnectedState)
        {
            client->write(message.toUtf8());
            emit logMessage(message);
        }
    }
}

void MyTcpServer::sendToClient(QTcpSocket *client, const QString &message)
{
    if (client && client->state() == QAbstractSocket::ConnectedState) {
        client->write(message.toUtf8());
    }
}

QStringList MyTcpServer::getAllUsernames() const
{
    QStringList usernames;
    for (auto it = clientUsernames.begin(); it != clientUsernames.end(); ++it) {
        usernames << it.value();
    }
    return usernames;
}

void MyTcpServer::broadcastUserList()
{
    QStringList usernames = getAllUsernames();

    QString userListMsg = "userlist:" + usernames.join("|") + "|" +(musicplayerpagePtr->GetUserName() + " (admin)")  +"\n";

    for (QTcpSocket *client : clients)
    {
        if (client->state() == QAbstractSocket::ConnectedState)
        {
            client->write(userListMsg.toUtf8());
        }
    }
    emit updateDeviceList(usernames);
}

void MyTcpServer::removeUserByUsername(const QString &username)
{
    QTcpSocket *targetSocket = nullptr;

    for (auto it = clientUsernames.begin(); it != clientUsernames.end(); ++it) {
        if (it.value() == username) {
            targetSocket = it.key();
            break;
        }
    }

    if (!targetSocket) {
        qDebug() << "User not found:" << username;
        return;
    }

    targetSocket->disconnectFromHost();
}
