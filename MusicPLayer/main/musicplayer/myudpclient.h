#ifndef MYUDPCLIENT_H
#define MYUDPCLIENT_H

#include <QObject>
#include <QUdpSocket>

class MyUdpClient : public QObject
{
    Q_OBJECT

public:
    explicit MyUdpClient(QObject *parent = nullptr);
    void sendMessage(const QString &message, const QHostAddress &host, quint16 port);

signals:
    void logMessage(const QString &msg);

private slots:
    void onReadyRead();

private:
    QUdpSocket *udpSocket;
};

#endif // MYUDPCLIENT_H
