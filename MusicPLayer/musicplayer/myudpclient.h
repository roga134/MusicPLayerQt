#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStandardItemModel>

class musicplayerpage;

class MyTcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpClient(QObject *parent = nullptr);
    void connectToServer(const QHostAddress &host, quint16 port);
    void sendMessage(const QString &message);
    void setMusicPlayerPage(musicplayerpage *page);
    QString getServerUsername() const{return serveruser;}
    QStringList getAllUsernames() const{return currusers;}

signals:
    void updateDeviceList(const QStringList &userList);
    void logMessage(const QString &msg);
    void playMusicRequestedclient();
    void messageReceived(const QString &message, const QString &sender);
    void adminNameReceived(const QString &adminName);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *tcpSocket;
    musicplayerpage *musicplayerpagePtr = nullptr;
    QString serveruser = "";
    QStringList currusers;


};

#endif // MYTCPCLIENT_H
