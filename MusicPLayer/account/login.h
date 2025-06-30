#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QLabel>
#include <QProcess>
#include "menu.h"

namespace Ui {
class LogIn;
}

class menu;

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_enter_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::LogIn *ui;
    QLabel *background = nullptr;
    menu *mymenu;
};

#endif // LOGIN_H
