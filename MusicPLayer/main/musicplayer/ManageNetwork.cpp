#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::addLogMessage(const QString &msg)
{
    QMetaObject::invokeMethod(this, [=]()
    {
        QStandardItem *item = new QStandardItem(msg);
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
        if (!logmodel) logmodel = new QStandardItemModel(this);
        logmodel->appendRow(item);
        QModelIndex lastIndex = logmodel->index(logmodel->rowCount() - 1, 0);
        ui->generalListView->scrollTo(lastIndex);
    }, Qt::QueuedConnection);
}

void musicplayerpage::on_pushButton_server_clicked()
{
    if(is_server == 1)
    {
        addLogMessage("You have clicked this once");
        return;
    }
    else if(is_server == 2)
    {
        addLogMessage("You are client");
        return;
    }
    is_server = 1;

    ui->generalListView->setModel(logmodel);
    udpServer->startServer(1234);
}

void musicplayerpage::on_pushButton_client_clicked()
{
    if(is_server == 2)
    {
        addLogMessage("You have clicked this once");
        return;
    }
    else if(is_server == 1)
    {
        addLogMessage("You are server");
        return;
    }
    is_server = 2;

    ui->generalListView->setModel(logmodel);
    udpClient->sendMessage("Hello UDP Server!", QHostAddress("127.0.0.1"), 1234);
}

void musicplayerpage::handleplaybutton()
{
    if(is_server == 0)
    {
        return;
    }
    else if (is_server == 1)
    {
        udpServer->sendToClient(QHostAddress("127.0.0.1") , 1234,  "pause");
        addLogMessage("Sent 'pause' message to client");

        return;
    }
    else
    {
        QString message = "pause";
        QHostAddress serverAddress = QHostAddress("127.0.0.1");
        quint16 port = 1234;
        udpClient->sendMessage(message, serverAddress, port);
        return;
    }
}
