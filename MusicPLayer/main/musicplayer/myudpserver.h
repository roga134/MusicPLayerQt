#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QObject>
#include <QUdpSocket>

class MyUdpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyUdpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);

signals:
    void logMessage(const QString &msg);

private slots:
    void onReadyRead();

private:
    QUdpSocket *udpSocket;
};

#endif // MYUDPSERVER_H
