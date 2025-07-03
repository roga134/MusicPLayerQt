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
    ui->generalListView->setStyleSheet("");
    chatLineEdit->hide();
    sendButton->hide();
    chatActive = false;

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

    ui->generalListView->setModel(logmodel);
    if (is_server == 1)
    {
        addLogMessage("you have clicked this button");
        return;
    }
    else if (is_server == 2)
    {
        addLogMessage("you are client");
        return;
    }
    //mach_songs = false;
    is_server = 1;
    tcpServer->startServer(1234);
}

void musicplayerpage::on_pushButton_client_clicked()
{
    ui->generalListView->setStyleSheet("");
    chatLineEdit->hide();
    sendButton->hide();
    chatActive = false;

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


    ui->generalListView->setModel(logmodel);
    if(is_server == 1)
    {
        addLogMessage("you are server");
        return;
    }
    else if (is_server == 2)
    {
        addLogMessage("you have clicked this button");
        return;
    }
    //mach_songs = false;
    is_server = 2;

    ui->generalListView->setModel(logmodel);
    tcpClient->connectToServer(QHostAddress("127.0.0.1"), 1234);
}


void musicplayerpage::handleplaybutton()
{
    if (is_server == 1)
    {
        if (ispause)
        {
            tcpServer->sendToAllClients("play");
            addLogMessage("Sent 'play' to all clients");
        }
        else
        {
            tcpServer->sendToAllClients("pause");
            addLogMessage("Sent 'pause' to all clients");
        }

        QTimer::singleShot(100, this, [=]() 
        {
            tcpServer->sendToAllClients("inplay:" + currentTrack->fileName());
        });
    }
    else if (is_server == 2)
    {
        if (ispause)
        {
            tcpClient->sendMessage("play");
        }
        else
        {
            tcpClient->sendMessage("pause");
        }


        QTimer::singleShot(100, this, [=]() 
        {
            tcpClient->sendMessage("inplay:" + currentTrack->fileName());
        });
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


    connect(chatLineEdit, &QLineEdit::returnPressed, this, [this]() {
        QString message = chatLineEdit->text().trimmed();
        if (!message.isEmpty())
        {
            addChatMessage(message, true);
            chatLineEdit->clear();

            if (is_server == 1)
            {
                if(message == "play" || message =="pause")
                {
                    play_pause_network();
                }

                tcpServer->sendToAllClients(message);
            }
            else
            {
                if(message == "play" || message =="pause")
                {
                    play_pause_network();
                }
                tcpClient->sendMessage(message);
            }
        }
    });


    connect(sendButton, &QPushButton::clicked, this, [this]() {
        QString text = chatLineEdit->text().trimmed();
        if (!text.isEmpty()) {
            if (is_server == 1)
                tcpServer->sendToAllClients(text);
            else if (is_server == 2)
                tcpClient->sendMessage(text);

            chatLineEdit->clear();
        }
    });
}

void musicplayerpage::addChatMessage(const QString &message, bool isMyMessage)
{
    QStandardItem *item = new QStandardItem(message);
    item->setTextAlignment(isMyMessage ? Qt::AlignRight : Qt::AlignLeft);

    QString style;
    if(isMyMessage)
    {
        style = "background-color: #ADD8E6; border-radius: 12px; padding: 8px 12px;";
    }
    else
    {
        style = "background-color: #FFFFFF; border-radius: 12px; padding: 8px 12px; border: 1px solid #E5E5EA;";
    }

    item->setData(style, Qt::UserRole);


    if(isMyMessage) {
        item->setBackground(QBrush(QColor(220, 248, 203)));
    } else
    {
        item->setBackground(QBrush(QColor(255, 255, 255)));
    }

    chatModel->appendRow(item);
    ui->generalListView->scrollToBottom();
}

void musicplayerpage::on_pushButton_devices_clicked()
{
    ui->generalListView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->generalListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->generalListView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->generalListView->setFocusPolicy(Qt::NoFocus);



    if (is_server == 1)
    {
        QStringList usernames = tcpServer->getAllUsernames();
        QString serverUsername = GetUserName();

        if (!usernames.contains(serverUsername))
        {
            usernames.append(serverUsername);
        }

        QAbstractItemModel *oldModel = ui->generalListView->model();
        if (oldModel) {
            delete oldModel;
        }
        QStandardItemModel *userModel = new QStandardItemModel(this);

        userModel = new QStandardItemModel(this);
        for (const QString &name : usernames)
        {
            QString displayName = name;
            if (name == serverUsername)
                displayName += " (admin)";

            QStandardItem *item = new QStandardItem(displayName);
            item->setEditable(false);
            userModel->appendRow(item);
            ui->generalListView->setModel(userModel);
        }
    }
    else if (is_server == 2)
    {
        tcpClient->sendMessage("request_user_list");

        QStringList usernames = tcpClient->getAllUsernames();
        QString serverUsername = tcpClient->getServerUsername();

        updateDeviceList(usernames);

        QAbstractItemModel *oldModel = ui->generalListView->model();
        if (oldModel) {
            delete oldModel;
        }
        QStandardItemModel *userModel = new QStandardItemModel(this);

        userModel = new QStandardItemModel(this);
        for (const QString &name : usernames)
        {
            QString displayName = name;
            if (name == serverUsername)
                displayName += " (admin)";

            QStandardItem *item = new QStandardItem(displayName);
            item->setEditable(false);
            userModel->appendRow(item);

            ui->generalListView->setModel(userModel);
        }
    }
}

void musicplayerpage::updateDeviceList(const QStringList &usernames)
{
    if (!this->isVisible()) return;

    QString serverUsername;

    if(is_server == 2)
    {
        serverUsername = tcpClient->getServerUsername();
    }
    else
    {
        serverUsername = this->GetUserName();
    }
    QStandardItemModel *userModel = new QStandardItemModel(this);

    for (const QString &name : usernames)
    {
        QString displayName = name;
        if (name == serverUsername)
            displayName += " (admin)";

        QStandardItem *item = new QStandardItem(displayName);
        item->setEditable(false);
        userModel->appendRow(item);
    }
}

void musicplayerpage::showUserContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->generalListView->indexAt(pos);
    if (!index.isValid())
        return;

    QString selectedUser = index.data().toString();
    selectedUser = selectedUser.replace(" (admin)", "");

    QMenu contextMenu;
    QAction *removeAction = contextMenu.addAction("Remove User");

    QAction *selectedAction = contextMenu.exec(ui->generalListView->viewport()->mapToGlobal(pos));
    if (selectedAction == removeAction)
    {
        if (is_server == 1)
        {
            emit requestUserRemoval(selectedUser);
        }
        else
        {
            QMessageBox::information(this, "Permission Denied", "Only the server can remove users.");
        }
    }
}


void musicplayerpage::onAdminNameReceived(const QString &adminName)
{
    serveruser = adminName;
}
QString musicplayerpage::getfilesong ()
{
    return currentTrack->toLocalFile();
}
