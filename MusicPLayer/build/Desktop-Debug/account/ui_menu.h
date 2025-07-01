/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_logIn;
    QPushButton *pushButton_signUp;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_forPass;
    QPushButton *pushButton_exit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(986, 416);
        centralwidget = new QWidget(menu);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_logIn = new QPushButton(centralwidget);
        pushButton_logIn->setObjectName("pushButton_logIn");
        pushButton_logIn->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_logIn->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_logIn);

        pushButton_signUp = new QPushButton(centralwidget);
        pushButton_signUp->setObjectName("pushButton_signUp");
        pushButton_signUp->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_signUp->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        horizontalLayout->addWidget(pushButton_signUp);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton_forPass = new QPushButton(centralwidget);
        pushButton_forPass->setObjectName("pushButton_forPass");
        pushButton_forPass->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_forPass->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        verticalLayout->addWidget(pushButton_forPass);

        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName("pushButton_exit");
        pushButton_exit->setCursor(QCursor(Qt::CursorShape::OpenHandCursor));
        pushButton_exit->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 203, 203);"));

        verticalLayout->addWidget(pushButton_exit);


        verticalLayout_2->addLayout(verticalLayout);

        menu->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(menu);
        statusbar->setObjectName("statusbar");
        menu->setStatusBar(statusbar);

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QMainWindow *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("menu", "<html><head/><body><p><span style=\" font-size:22pt; color:#ffffff;\">Welcome To The MusicPlayer</span></p></body></html>", nullptr));
        label_2->setText(QString());
        pushButton_logIn->setText(QCoreApplication::translate("menu", "Login", nullptr));
        pushButton_signUp->setText(QCoreApplication::translate("menu", "SignUp", nullptr));
        pushButton_forPass->setText(QCoreApplication::translate("menu", "ForgetPassword", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("menu", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
