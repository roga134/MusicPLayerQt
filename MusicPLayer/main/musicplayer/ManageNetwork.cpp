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
    ui->generalListView->setModel(logmodel);
    udpServer->startServer(1234);
}

void musicplayerpage::on_pushButton_client_clicked()
{
    ui->generalListView->setModel(logmodel);
    udpClient->sendMessage("Hello UDP Server!", QHostAddress("127.0.0.1"), 12345);
}
