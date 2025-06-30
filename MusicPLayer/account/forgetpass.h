#ifndef FORGETPASS_H
#define FORGETPASS_H

#include <QMainWindow>
#include <QLabel>
#include "menu.h"

namespace Ui {
class ForgetPass;
}

class menu;

class ForgetPass : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForgetPass(QWidget *parent = nullptr);
    ~ForgetPass();
    void CheckPass();

signals:
    void upPressed();
    void downPressed();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_Done_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void keyPressEvent(QKeyEvent *event);


private:
    Ui::ForgetPass *ui;
    QLabel *background = nullptr;
    menu *mymenu;
};

#endif // FORGETPASS_H
