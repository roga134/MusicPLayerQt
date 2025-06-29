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
    {
        emit logMessage(QString("UDP Server started on port %1").arg(port));
    }
    else
    {
        emit logMessage(QString("Failed to start UDP Server: %1").arg(udpSocket->errorString()));
    }
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

        emit logMessage(QString("Received from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));

        QByteArray response = "Hello UDP client!";
        udpSocket->writeDatagram(response, sender, senderPort);
    }
}
