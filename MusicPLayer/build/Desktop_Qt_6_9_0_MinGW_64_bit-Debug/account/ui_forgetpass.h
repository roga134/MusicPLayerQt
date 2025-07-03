/********************************************************************************
** Form generated from reading UI file 'forgetpass.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGETPASS_H
#define UI_FORGETPASS_H

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

class Ui_ForgetPass
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_username;
    QLabel *label_secure;
    QLabel *label_confpass;
    QLabel *label_pass;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_Pass;
    QLineEdit *lineEdit_confPass;
    QLineEdit *lineEdit_secure;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_back;
    QPushButton *pushButton_Done;

    void setupUi(QMainWindow *ForgetPass)
    {
        if (ForgetPass->objectName().isEmpty())
            ForgetPass->setObjectName("ForgetPass");
        ForgetPass->resize(716, 334);
        centralwidget = new QWidget(ForgetPass);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_username = new QLabel(centralwidget);
        label_username->setObjectName("label_username");

        gridLayout_2->addWidget(label_username, 0, 0, 1, 1);

        label_secure = new QLabel(centralwidget);
        label_secure->setObjectName("label_secure");

        gridLayout_2->addWidget(label_secure, 1, 0, 1, 1);

        label_confpass = new QLabel(centralwidget);
        label_confpass->setObjectName("label_confpass");

        gridLayout_2->addWidget(label_confpass, 3, 0, 1, 1);

        label_pass = new QLabel(centralwidget);
        label_pass->setObjectName("label_pass");

        gridLayout_2->addWidget(label_pass, 2, 0, 1, 1);

        lineEdit_username = new QLineEdit(centralwidget);
        lineEdit_username->setObjectName("lineEdit_username");

        gridLayout_2->addWidget(lineEdit_username, 0, 1, 1, 1);

        lineEdit_Pass = new QLineEdit(centralwidget);
        lineEdit_Pass->setObjectName("lineEdit_Pass");
        lineEdit_Pass->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_Pass, 2, 1, 1, 1);

        lineEdit_confPass = new QLineEdit(centralwidget);
        lineEdit_confPass->setObjectName("lineEdit_confPass");
        lineEdit_confPass->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_confPass, 3, 1, 1, 1);

        lineEdit_secure = new QLineEdit(centralwidget);
        lineEdit_secure->setObjectName("lineEdit_secure");

        gridLayout_2->addWidget(lineEdit_secure, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_back->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout_2->addWidget(pushButton_back);

        pushButton_Done = new QPushButton(centralwidget);
        pushButton_Done->setObjectName("pushButton_Done");
        pushButton_Done->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_Done->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout_2->addWidget(pushButton_Done);


        verticalLayout->addLayout(horizontalLayout_2);

        ForgetPass->setCentralWidget(centralwidget);

        retranslateUi(ForgetPass);

        QMetaObject::connectSlotsByName(ForgetPass);
    } // setupUi

    void retranslateUi(QMainWindow *ForgetPass)
    {
        ForgetPass->setWindowTitle(QCoreApplication::translate("ForgetPass", "MainWindow", nullptr));
        label_username->setText(QCoreApplication::translate("ForgetPass", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">User name :</span></p></body></html>", nullptr));
        label_secure->setText(QCoreApplication::translate("ForgetPass", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Your pet name :</span></p></body></html>", nullptr));
        label_confpass->setText(QCoreApplication::translate("ForgetPass", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Confirm password : </span></p></body></html>", nullptr));
        label_pass->setText(QCoreApplication::translate("ForgetPass", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">Password :</span></p></body></html>", nullptr));
        pushButton_back->setText(QCoreApplication::translate("ForgetPass", "Back", nullptr));
        pushButton_Done->setText(QCoreApplication::translate("ForgetPass", "Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForgetPass: public Ui_ForgetPass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGETPASS_H
