// MyUdpClient.cpp
#include "myudpclient.h"

MyUdpClient::MyUdpClient(QObject *parent)
    : QObject(parent), udpSocket(new QUdpSocket(this))
{
    connect(udpSocket, &QUdpSocket::readyRead, this, &MyUdpClient::onReadyRead);

    quint16 clientPort = 45454 ;

    if (!udpSocket->bind(QHostAddress::AnyIPv4, clientPort))
    {
        emit logMessage(QString("Failed to bind UDP client: %1").arg(udpSocket->errorString()));
    }
    else
    {
        emit logMessage(QString("UDP Client listening on port %1").arg(clientPort));
    }
}

void MyUdpClient::sendMessage(const QString &message, const QHostAddress &host, quint16 port)
{
    QByteArray data = message.toUtf8();
    udpSocket->writeDatagram(data, host, port);
    emit logMessage(QString("Sent to %1:%2 - %3").arg(host.toString()).arg(port).arg(message));
}

void MyUdpClient::onReadyRead()
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
        emit messageReceived(msg, sender.toString());

        if (msg == "play_music")
        {
            //emit playMusicRequested();
        }
        else if (msg == "stop_music")
        {
            //emit stopMusicRequested();
        }
    }
}
