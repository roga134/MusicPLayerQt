#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::setinformation(QString firstName,QString lastName,QString username,QString email)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->username = username;
    this->email = email;
}

void musicplayerpage::on_pushButton_info_clicked()
{
    ui->generalListView->setStyleSheet("");
    chatLineEdit->hide();
    sendButton->hide();
    chatActive = false;


    ui->generalListView->setModel(infotModel);
    ui->generalListView->setItemDelegate(infotDelegate);

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

    infotModel->clear();

    infotModel->appendRow(new QStandardItem("First Name: " + firstName));
    infotModel->appendRow(new QStandardItem("Last Name: " + lastName));
    infotModel->appendRow(new QStandardItem("Username: " + username));
    infotModel->appendRow(new QStandardItem("Email: " + email));
}
