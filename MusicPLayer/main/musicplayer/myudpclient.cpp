// MyUdpClient.cpp
#include "myudpclient.h"

MyUdpClient::MyUdpClient(QObject *parent)
    : QObject(parent), udpSocket(new QUdpSocket(this))
{
    connect(udpSocket, &QUdpSocket::readyRead, this, &MyUdpClient::onReadyRead);
}

void MyUdpClient::sendMessage(const QString &message, const QHostAddress &host, quint16 port)
{
    QByteArray data = message.toUtf8();
    udpSocket->writeDatagram(data, host, port);
    emit logMessage(QString("Sent to %1:%2 - %3").arg(host.toString()).arg(port).arg(message));
}

void MyUdpClient::onReadyRead()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        emit logMessage(QString("Received from %1:%2 - %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));
    }
}
