#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QSet>
#include <QPair>

class MyUdpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyUdpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void sendToAllClients(const QString &message);
    void sendToClient(const QHostAddress &address, quint16 port, const QString &message);

signals:
    void logMessage(const QString &msg);
    void playMusicRequested();
    void messageReceived(const QString &message, const QString &sender);

private slots:
    void onReadyRead();

private:
    QUdpSocket *udpSocket;
    QSet<QPair<QHostAddress, quint16>> clients;
};

#endif // MYUDPSERVER_H
