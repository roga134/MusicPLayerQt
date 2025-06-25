#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QLabel>
#include "menu.h"
#include "login.h"

namespace Ui {
class SignUp;
}

class menu;
class LogIn;

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
    void WriteOnFile();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_login_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::SignUp *ui;
    QLabel *background = nullptr;
    menu *mymenu;
    LogIn *login;
};

#endif // SIGNUP_H
