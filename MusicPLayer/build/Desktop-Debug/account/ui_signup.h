/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

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

class Ui_SignUp
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_SecureCode;
    QLabel *label_Email;
    QLabel *label_Pass;
    QLabel *label_ConfPass;
    QLabel *label_LastName;
    QLabel *label_UserName;
    QLabel *label_FirstName;
    QLineEdit *lineEdit_Pass;
    QLineEdit *lineEdit_ConfPass;
    QLineEdit *lineEdit_Email;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_LastName;
    QLineEdit *lineEdit_FirstName;
    QLineEdit *lineEdit_SecureCode;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_back;
    QPushButton *pushButton_login;

    void setupUi(QMainWindow *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(870, 341);
        centralwidget = new QWidget(SignUp);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_SecureCode = new QLabel(centralwidget);
        label_SecureCode->setObjectName("label_SecureCode");

        gridLayout->addWidget(label_SecureCode, 6, 1, 1, 1);

        label_Email = new QLabel(centralwidget);
        label_Email->setObjectName("label_Email");

        gridLayout->addWidget(label_Email, 3, 1, 1, 1);

        label_Pass = new QLabel(centralwidget);
        label_Pass->setObjectName("label_Pass");

        gridLayout->addWidget(label_Pass, 4, 1, 1, 1);

        label_ConfPass = new QLabel(centralwidget);
        label_ConfPass->setObjectName("label_ConfPass");

        gridLayout->addWidget(label_ConfPass, 5, 1, 1, 1);

        label_LastName = new QLabel(centralwidget);
        label_LastName->setObjectName("label_LastName");

        gridLayout->addWidget(label_LastName, 1, 1, 1, 1);

        label_UserName = new QLabel(centralwidget);
        label_UserName->setObjectName("label_UserName");

        gridLayout->addWidget(label_UserName, 2, 1, 1, 1);

        label_FirstName = new QLabel(centralwidget);
        label_FirstName->setObjectName("label_FirstName");

        gridLayout->addWidget(label_FirstName, 0, 1, 1, 1);

        lineEdit_Pass = new QLineEdit(centralwidget);
        lineEdit_Pass->setObjectName("lineEdit_Pass");
        lineEdit_Pass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_Pass, 4, 2, 1, 1);

        lineEdit_ConfPass = new QLineEdit(centralwidget);
        lineEdit_ConfPass->setObjectName("lineEdit_ConfPass");
        lineEdit_ConfPass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_ConfPass, 5, 2, 1, 1);

        lineEdit_Email = new QLineEdit(centralwidget);
        lineEdit_Email->setObjectName("lineEdit_Email");

        gridLayout->addWidget(lineEdit_Email, 3, 2, 1, 1);

        lineEdit_UserName = new QLineEdit(centralwidget);
        lineEdit_UserName->setObjectName("lineEdit_UserName");

        gridLayout->addWidget(lineEdit_UserName, 2, 2, 1, 1);

        lineEdit_LastName = new QLineEdit(centralwidget);
        lineEdit_LastName->setObjectName("lineEdit_LastName");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_LastName->sizePolicy().hasHeightForWidth());
        lineEdit_LastName->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit_LastName, 1, 2, 1, 1);

        lineEdit_FirstName = new QLineEdit(centralwidget);
        lineEdit_FirstName->setObjectName("lineEdit_FirstName");

        gridLayout->addWidget(lineEdit_FirstName, 0, 2, 1, 1);

        lineEdit_SecureCode = new QLineEdit(centralwidget);
        lineEdit_SecureCode->setObjectName("lineEdit_SecureCode");

        gridLayout->addWidget(lineEdit_SecureCode, 6, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_back = new QPushButton(centralwidget);
        pushButton_back->setObjectName("pushButton_back");
        pushButton_back->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_back->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_back);

        pushButton_login = new QPushButton(centralwidget);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_login->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_login);


        verticalLayout->addLayout(horizontalLayout);

        SignUp->setCentralWidget(centralwidget);

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QMainWindow *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "MainWindow", nullptr));
        label_SecureCode->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">Your pet name :</span></p></body></html>", nullptr));
        label_Email->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">Email :</span></p></body></html>", nullptr));
        label_Pass->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">Password :</span></p></body></html>", nullptr));
        label_ConfPass->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#ffffff;\">Confirm password :</span></p></body></html>", nullptr));
        label_LastName->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">LastName :</span></p></body></html>", nullptr));
        label_UserName->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">UserName :</span></p></body></html>", nullptr));
        label_FirstName->setText(QCoreApplication::translate("SignUp", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">FirstName :</span></p></body></html>", nullptr));
        pushButton_back->setText(QCoreApplication::translate("SignUp", "Back", nullptr));
        pushButton_login->setText(QCoreApplication::translate("SignUp", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
