#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class musicplayerpage;

class MyTcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpClient(QObject *parent = nullptr);
    void connectToServer(const QHostAddress &host, quint16 port);
    void sendMessage(const QString &message);
    void setMusicPlayerPage(musicplayerpage *page);

signals:
    void logMessage(const QString &msg);
    void playMusicRequestedclient();
    void messageReceived(const QString &message, const QString &sender);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *tcpSocket;
    musicplayerpage *musicplayerpagePtr = nullptr;

};

#endif // MYTCPCLIENT_H
