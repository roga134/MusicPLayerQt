#include "myudpclient.h"
#include "musicplayerpage.h"

MyTcpClient::MyTcpClient(QObject *parent)
    : QObject(parent), tcpSocket(new QTcpSocket(this))
{
    connect(tcpSocket, &QTcpSocket::readyRead, this, &MyTcpClient::onReadyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &MyTcpClient::onDisconnected);
}

void MyTcpClient::connectToServer(const QHostAddress &host, quint16 port)
{
    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, [this]()
    {
        tcpSocket->write(musicplayerpagePtr->GetUserName().toUtf8());
    });
}

void MyTcpClient::sendMessage(const QString &message)
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        tcpSocket->write(message.toUtf8());
        emit logMessage(QString("Sent: %1").arg(message));
    }
    else
    {
        emit logMessage("Cannot send: not connected to server.");
    }
}

void MyTcpClient::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    QString msg = QString::fromUtf8(data).trimmed();

    QString songName = msg.mid(QString("inplay:").length());
    if (msg.startsWith("inplay:"))
    {
        emit playSpecificSongRequested(songName);
        return;
    }

    if (msg.startsWith("FILE:"))
    {
        // --- استخراج اطلاعات فایل از هدر ---
        QList<QByteArray> parts = data.split('\n');
        QByteArray headerLine = parts[0]; // مثلا "FILE:mysong.mp3:123456"

        QList<QByteArray> headerParts = headerLine.mid(5).split(':');
        if (headerParts.size() < 2) return;

        QString fileName = QString::fromUtf8(headerParts[0]);
        int fileSize = headerParts[1].toInt();

        // --- بررسی و دریافت DATA: ---
        QByteArray rawData = data;
        int dataIndex = rawData.indexOf("DATA:");
        if (dataIndex == -1) {
            qDebug() << "DATA: prefix not found!";
            return;
        }

        QByteArray fileData = rawData.mid(dataIndex + 5); // داده باینری بعد از "DATA:"

        if (fileData.size() < fileSize) {
            qDebug() << "File data incomplete. Waiting for remaining bytes...";
            // نکته: برای انتقال‌های بزرگ باید از buffer استفاده کنی و در چند مرحله بخونی.
            return;
        }

        // --- ذخیره فایل ---
        QFile outFile(QDir::homePath() + "/Downloads/" + fileName); // مسیر دلخواه
        if (outFile.open(QIODevice::WriteOnly)) {
            outFile.write(fileData.left(fileSize));
            outFile.close();
            emit logMessage("File received and saved: " + fileName);
        } else {
            emit logMessage("Cannot save file: " + fileName);
        }
        return;
    }


    if (serveruser.isEmpty())
    {
        if (msg.startsWith("admin:"))
        {
            serveruser = msg.mid(QString("admin:").length());
            emit logMessage("Server admin username set to: " + serveruser);
        }
        else
        {
            serveruser = msg;
            emit logMessage("Server username set to: " + serveruser);
        }
        return;
    }

    if (msg.startsWith("userlist:"))
    {
        QStringList userList = msg.mid(QString("userlist:").length()).split("|");

        currusers = userList;
        emit updateDeviceList(userList);
        return;
    }

    int sepIndex = msg.indexOf(": ");
    if (sepIndex != -1)
    {
        QString sender = msg.left(sepIndex);
        QString message = msg.mid(sepIndex + 2);
        emit logMessage(sender + ": " + message);
        emit messageReceived(message, sender);
    }
    else
    {
        emit messageReceived("(admin) " +msg, serveruser);
    }

}
void MyTcpClient::onDisconnected()
{
    emit logMessage("Disconnected from server.");
    musicplayerpagePtr->addChatMessage("Disconnected from server." , false);
}

void MyTcpClient::setMusicPlayerPage(musicplayerpage *page)
{
    try {
        if (!page) {
            throw std::runtime_error("Null pointer passed to setMusicPlayerPage");
        }
        musicplayerpagePtr = page;
    } catch (const std::exception &e) {
        emit logMessage(QString("Error setting music player page: %1").arg(e.what()));
    } catch (...) {
        emit logMessage("Unknown error setting music player page");
    }
}
