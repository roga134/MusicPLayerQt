#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::addLogMessage(const QString &msg)
{
    QMetaObject::invokeMethod(this, [=]() {
        QStandardItem *item = new QStandardItem(msg);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        if (!logmodel) logmodel = new QStandardItemModel(this);
        logmodel->appendRow(item);
        QModelIndex lastIndex = logmodel->index(logmodel->rowCount() - 1, 0);
        ui->generalListView->scrollTo(lastIndex);
    }, Qt::QueuedConnection);
}

void musicplayerpage::runServer()
{
    server = new QTcpServer();

    QObject::connect(server, &QTcpServer::newConnection, [=]()
    {
        QTcpSocket *clientSocket = server->nextPendingConnection();

        addLogMessage("New client connected:" + clientSocket->peerAddress().toString());

        QObject::connect(clientSocket, &QTcpSocket::readyRead, [this, clientSocket]() {
            QByteArray data = clientSocket->readAll();
            addLogMessage("Received: " + data);
            clientSocket->write("Hello from server\n");
        });

        QObject::connect(clientSocket, &QTcpSocket::disconnected, [this, clientSocket]() {
            addLogMessage("Client disconnected");
            clientSocket->deleteLater();
        });
    });

    if (!server->listen(QHostAddress::Any, 1234))
    {
        addLogMessage("Server could not start!");
        return;
    }

    addLogMessage("Server started on port 1234");
}

void musicplayerpage::serverThreadFunction()
{
    QEventLoop loop;

    runServer();

    loop.exec();
}

void musicplayerpage::runClient()
{
    clientsocket = new QTcpSocket();

    QObject::connect(clientsocket, &QTcpSocket::connected, [this]() {
        addLogMessage("Client connected to server");
    });

    QObject::connect(clientsocket, &QTcpSocket::readyRead, [this]() {
        QByteArray data = clientsocket->readAll();
        addLogMessage("Client received:" + data);
    });

    QObject::connect(clientsocket, &QTcpSocket::connected, [=]() {
        addLogMessage("Connected");
    });

    QTimer::singleShot(1000, [this]() {
        clientsocket->connectToHost("127.0.0.1", 1234);
    });
}

void musicplayerpage::clientThreadFunction()
{
    QEventLoop loop;

    runServer();

    loop.exec();
}

void musicplayerpage::sendMessageToServer(const QString &message)
{
    if (clientsocket && clientsocket->state() == QAbstractSocket::ConnectedState)
    {
        clientsocket->write(message.toUtf8());
        addLogMessage("Sent to server: " + message);
    }
    else
    {
        addLogMessage("Client not connected. Cannot send message.");
    }
}

void musicplayerpage::on_pushButton_internet_clicked()
{
    ui->generalListView->setModel(logmodel);

    threadServer = new QThread(this);

    this->moveToThread(threadServer);

    connect(threadServer, &QThread::started, this, &musicplayerpage::runServer);
    connect(threadServer, &QThread::finished, threadServer, &QObject::deleteLater);
    threadServer->start();

    threadClient = new QThread(this);
    connect(threadClient, &QThread::started, this, &musicplayerpage::runClient);
    connect(threadClient, &QThread::finished, threadClient, &QObject::deleteLater);
    threadClient->start();
}

/*
 *     clientsocket = new QTcpSocket(this);
    clientsocket->connectToHost("127.0.0.1", 1234);
    if (clientsocket->waitForConnected(4000))
    {
        addLogMessage("client : Connected to server");

        QByteArray message = "client : Hello Server!";
        clientsocket->write(message);

        if (clientsocket->waitForBytesWritten(4000))
        {
            if (clientsocket->waitForReadyRead(4000))
            {
                QByteArray response = clientsocket->readAll();
                addLogMessage("client : Received from server:" + response);
            }
            else
            {
                addLogMessage("client : No response from server");
            }
        }
        else
        {
            addLogMessage("client : Failed to write data");
        }

        clientsocket->disconnectFromHost();
        clientsocket->waitForDisconnected();
    }
    else
    {
        qDebug() << "Failed to connect to server";
    }*/
/*
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    MyServer server;
    if (!server.listen(QHostAddress::Any, 12345)) {
        qDebug() << "Server failed to start!";
        return -1;
    }
    qDebug() << "Server started on port 12345";
    return app.exec();
}*/

/*
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("X.tcp.ngrok.io", YYYYY); // آدرس و پورت ngrok رو جایگزین کن

    QObject::connect(&socket, &QTcpSocket::connected, [&]() {
        qDebug() << "Connected to server!";
        socket.write("Hello from client");
    });

    QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {
        QByteArray data = socket.readAll();
        qDebug() << "Received from server:" << data;
    });

    QObject::connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [&](QAbstractSocket::SocketError socketError) {
        qDebug() << "Socket error:" << socket.errorString();
    });

    return app.exec();
}*/
