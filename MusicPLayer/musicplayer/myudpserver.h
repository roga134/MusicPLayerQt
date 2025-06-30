#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QSet>
#include <QHash>
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
    void sendToClient(QTcpSocket *client, const QString &message);

signals:
    void logMessage(const QString &msg);
    void playMusicRequested();
    void messageReceived(const QString &message, const QString &sender);

private slots:
    void onNewConnection();
    void onReadyRead(QTcpSocket *clientSocket);
    void onDisconnected();

private:
    QTcpServer *tcpServer;
    QSet<QTcpSocket*> clients;
    QHash<QTcpSocket*, QString> clientUsernames;
    musicplayerpage *musicplayerpagePtr = nullptr;
};

#endif // MYUDPSERVER_H
