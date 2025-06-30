#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include "signup.h"
#include "login.h"
#include "forgetpass.h"

namespace Ui {
class menu;
}

class SignUp;
class LogIn;
class ForgetPass;

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_forPass_clicked();

    void on_pushButton_logIn_clicked();

    void on_pushButton_signUp_clicked();

private:
    Ui::menu *ui;
    QLabel *background = nullptr;
    SignUp *signup = nullptr;
    LogIn *login = nullptr;
    ForgetPass *forgetpass = nullptr;
};

#endif // MENU_H
