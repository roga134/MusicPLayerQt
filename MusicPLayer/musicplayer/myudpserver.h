#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

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
    QStringList getAllUsernames() const;
    void broadcastUserList();
    void removeUserByUsername(const QString &username);

signals:
    void logMessage(const QString &msg);
    void playMusicRequested();
    void messageReceived(const QString &message, const QString &sender);
    void updateDeviceList(const QStringList &userList);

private slots:
    void onNewConnection();
    void onReadyRead(QTcpSocket *clientSocket);
    void onDisconnected();

private:
    QString adminUsername;
    QTcpServer *tcpServer;
    QSet<QTcpSocket*> clients;
    QHash<QTcpSocket*, QString> clientUsernames;
    musicplayerpage *musicplayerpagePtr;
    QSet<QTcpSocket*> initializedClients;
    void forwardCommandToOthers(QTcpSocket* sender, const QString& command);
};

#endif // MYTCPSERVER_H
