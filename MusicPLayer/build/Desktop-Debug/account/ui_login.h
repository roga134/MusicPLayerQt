/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIn
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QLabel *label_pass;
    QLineEdit *lineEdit_pass;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_back;
    QPushButton *pushButton_enter;

    void setupUi(QMainWindow *LogIn)
    {
        if (LogIn->objectName().isEmpty())
            LogIn->setObjectName("LogIn");
        LogIn->resize(817, 214);
        LogIn->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(LogIn);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_username = new QLabel(centralwidget);
        label_username->setObjectName("label_username");

        gridLayout->addWidget(label_username, 0, 0, 1, 1);

        lineEdit_username = new QLineEdit(centralwidget);
        lineEdit_username->setObjectName("lineEdit_username");

        gridLayout->addWidget(lineEdit_username, 0, 1, 1, 1);

        label_pass = new QLabel(centralwidget);
        label_pass->setObjectName("label_pass");

        gridLayout->addWidget(label_pass, 1, 0, 1, 1);

        lineEdit_pass = new QLineEdit(centralwidget);
        lineEdit_pass->setObjectName("lineEdit_pass");
        lineEdit_pass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_pass, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_back->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_back);

        pushButton_enter = new QPushButton(centralwidget);
        pushButton_enter->setObjectName("pushButton_enter");
        pushButton_enter->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_enter->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_enter);


        verticalLayout->addLayout(horizontalLayout);

        LogIn->setCentralWidget(centralwidget);

        retranslateUi(LogIn);

        QMetaObject::connectSlotsByName(LogIn);
    } // setupUi

    void retranslateUi(QMainWindow *LogIn)
    {
        LogIn->setWindowTitle(QCoreApplication::translate("LogIn", "MainWindow", nullptr));
        label_username->setText(QCoreApplication::translate("LogIn", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#ffffff;\">Username :</span></p></body></html>", nullptr));
        label_pass->setText(QCoreApplication::translate("LogIn", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#ffffff;\">Password :</span></p></body></html>", nullptr));
        pushButton_back->setText(QCoreApplication::translate("LogIn", "Back", nullptr));
        pushButton_enter->setText(QCoreApplication::translate("LogIn", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIn: public Ui_LogIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
