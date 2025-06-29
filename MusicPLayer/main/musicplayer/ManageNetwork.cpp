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
void musicplayerpage::on_pushButton_chat_clicked()
{
    if(is_server == 0)
    {
        QMessageBox::warning(this,"Connection Error","You must connect as server/client first!");
        return;
    }



    if (chatActive)
    {
         chatLineEdit->hide();
         sendButton->hide();
        chatActive = false;
        ui->generalListView->setModel(logmodel);
        return;
    }
    ui->generalListView->setItemDelegate(chatDelegate);
    ui->generalListView->setStyleSheet(
        "QListView {"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #dee2e6;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QListView::item {"
        "   padding: 8px 12px;"
        "   border-radius: 12px;"
        "   margin: 4px 0;"
        "   font-size: 14px;"
        "}"
        "QListView::item:hover {"
        "   background-color: #e9ecef;"
        "}"
        );
    chatLineEdit->setStyleSheet(
        "QLineEdit {"
        "   border: 1px solid #ced4da;"
        "   border-radius: 15px;"
        "   padding: 5px 12px;"
        "   font-size: 14px;"
        "   background-color: white;"
        "}"
        "QLineEdit:focus {"
        "   border: 1px solid #80bdff;"
        "   outline: none;"
        "}"
        );
    sendButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #343a40;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 15px;"
        "   padding: 5px 15px;"
        "   font-size: 14px;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #23272b;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1d2124;"
        "}"
        );

    chatActive = true;
    ui->generalListView->setModel(chatModel);
    chatLineEdit->show();
    sendButton->show();




    connect(sendButton, &QPushButton::clicked, this, [this]() {
        QString message = chatLineEdit->text().trimmed();
        if (!message.isEmpty())
        {
            addChatMessage(message, true);
            chatLineEdit->clear();

            if(is_server == 1)
            {
                udpServer->sendToAllClients(message);
            }
            else
            {
                udpClient->sendMessage(message, QHostAddress("127.0.0.1"), 1234);
            }
        }
    });

}

void musicplayerpage::addChatMessage(const QString &message, bool isMyMessage)
{
    QStandardItem *item = new QStandardItem(message);
    item->setTextAlignment(isMyMessage ? Qt::AlignRight : Qt::AlignLeft);

    // استایل حباب پیام
    QString style;
    if(isMyMessage) {style = "background-color: #ADD8E6; border-radius: 12px; padding: 8px 12px;";
    } else {
        style = "background-color: #FFFFFF; border-radius: 12px; padding: 8px 12px; border: 1px solid #E5E5EA;";
    }

    item->setData(style, Qt::UserRole);


    if(isMyMessage) {
        item->setBackground(QBrush(QColor(220, 248, 203))); // سبز آبی بسیار روشن
    } else {
        item->setBackground(QBrush(QColor(255, 255, 255))); // سفید
    }

    chatModel->appendRow(item);
    ui->generalListView->scrollToBottom();
}
