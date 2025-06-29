#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QSet>
#include <QPair>
#include <QTcpServer>
#include <QTcpSocket>

class musicplayerpage;


class MyTcpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpServer(musicplayerpage *playerPage, QObject *parent = nullptr);
    bool startServer(quint16 port);
    void sendToAllClients(const QString &message);
    void sendToClient(const QHostAddress &address, quint16 port, const QString &message);

signals:
    void logMessage(const QString &msg);
    void playMusicRequested();
    void messageReceived(const QString &message, const QString &sender);

private slots:
    void onReadyRead(QTcpSocket *clientSocket);
    void onNewConnection();


private:
    QTcpServer *tcpServer;
    QSet<QTcpSocket*> clients;
    musicplayerpage *musicplayerpagePtr = nullptr;
    QHash<QTcpSocket*, bool> playlistSent;
};

#endif // MYUDPSERVER_H
