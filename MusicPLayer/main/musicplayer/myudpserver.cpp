// MyUdpServer.cpp
#include "myudpserver.h"

MyUdpServer::MyUdpServer(QObject *parent)
    : QObject(parent), udpSocket(new QUdpSocket(this))
{
    connect(udpSocket, &QUdpSocket::readyRead, this, &MyUdpServer::onReadyRead);
}


bool MyUdpServer::startServer(quint16 port)
{
    bool bound = udpSocket->bind(QHostAddress::AnyIPv4, port);
    if (bound)
        emit logMessage(QString("UDP Server started on port %1").arg(port));
    else
        emit logMessage(QString("Failed to start UDP Server: %1").arg(udpSocket->errorString()));
    return bound;
}

void MyUdpServer::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString msg = QString::fromUtf8(datagram);
        emit logMessage(QString("Received from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(msg));

        QPair<QHostAddress, quint16> clientKey(sender, senderPort);
        if (!clients.contains(clientKey))
            clients.insert(clientKey);

        QByteArray response = "Hello UDP client!";
        udpSocket->writeDatagram(response, sender, senderPort);

        QString command = QString(datagram).trimmed().toLower();
        if (command == "pause")
        {
            emit playMusicRequested();
        }
    }
}

void MyUdpServer::sendToAllClients(const QString &message)
{
    QByteArray data = message.toUtf8();
    for (const auto &client : std::as_const(clients)) {
        udpSocket->writeDatagram(data, client.first, client.second);
    }
    emit logMessage(QString("Sent to all clients: %1").arg(message));
}

void MyUdpServer::sendToClient(const QHostAddress &address, quint16 port, const QString &message)
{
    QByteArray data = message.toUtf8();
    udpSocket->writeDatagram(data, address, port);
    emit logMessage(QString("Sent to %1:%2 - %3").arg(address.toString()).arg(port).arg(message));
}
