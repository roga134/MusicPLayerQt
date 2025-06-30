#include "forgetpass.h"
#include "ui_forgetpass.h"
#include "encryption.h"
#include <QFont>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QPixmap>

ForgetPass::ForgetPass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgetPass)
{
    ui->setupUi(this);
    this->setWindowTitle("Recovery Page");

    background = new QLabel(this);
    background->lower();
    QFont font("Arial" , 12 , QFont::Bold);
    this->setFont(font);
    ui->pushButton_Done->setFont(font);
    ui->pushButton_back->setFont(font);

    connect(ui->lineEdit_Pass, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_confPass, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_secure, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_username, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);

    connect(this, &ForgetPass::downPressed, this, [=]() {
        if (ui->lineEdit_username->hasFocus())
            ui->lineEdit_secure->setFocus();
        else if (ui->lineEdit_secure->hasFocus())
            ui->lineEdit_Pass->setFocus();
        else if (ui->lineEdit_Pass->hasFocus())
            ui->lineEdit_confPass->setFocus();
        else if (ui->lineEdit_confPass->hasFocus())
            ui->pushButton_Done->setFocus();
    });

    connect(this, &ForgetPass::upPressed, this, [=]() {
        if (ui->lineEdit_confPass->hasFocus())
            ui->lineEdit_Pass->setFocus();
        else if (ui->lineEdit_Pass->hasFocus())
            ui->lineEdit_secure->setFocus();
        else if (ui->lineEdit_secure->hasFocus())
            ui->lineEdit_username->setFocus();
    });

}

ForgetPass::~ForgetPass()
{
    delete ui;
}

void ForgetPass::on_pushButton_back_clicked()
{
    this->close();
    mymenu = new menu(this);
    mymenu->show();
}

void ForgetPass::on_pushButton_Done_clicked()
{
    QFile file("information.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Cannot open file.");
        return ;
    }

    QTextStream in(&file);
    char key = 0x5A;

    QString inputUsername = ui->lineEdit_username->text();
    QString inputsecure = ui->lineEdit_secure->text();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        QString encryptedUsername = fields[2];
        QString decryptedUsername = simpleXOREncryptDecrypt(QByteArray::fromHex(encryptedUsername.toUtf8()), key);

        QString encryptedSecure = fields[5];
        QString decryptedSecyre = simpleXOREncryptDecrypt(QByteArray::fromHex(encryptedSecure.toUtf8()), key);

        if (decryptedUsername == inputUsername && decryptedSecyre == inputsecure)
        {
            CheckPass();
            return;
        }
    }

    file.close();
    QMessageBox::warning(this, "Login Failed", "Incorrect username or secure code.");
}

void ForgetPass::CheckPass()
{
    if (ui->lineEdit_Pass->text().isEmpty() || ui->lineEdit_confPass->text().isEmpty())
    {
        QMessageBox::warning(this, "Information Error", "The form is not complete");
        return;
    }

    if (ui->lineEdit_Pass->text() != ui->lineEdit_confPass->text())
    {
        QMessageBox::warning(this, "Password Error", "The password doesn't match");
        return;
    }

    QFile input_file("information.txt");
    QFile output_file("helper.txt");

    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Cannot open information file.");
        return;
    }

    if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Cannot open helper file.");
        input_file.close();
        return;
    }

    QTextStream in(&input_file);
    QTextStream out(&output_file);
    char key = 0x5A;

    QString inputUsername = ui->lineEdit_username->text();
    QString inputSecure = ui->lineEdit_secure->text();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() < 6)
        {
            out << line << "\n";
            continue;
        }

        QString decryptedUsername = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[2].toUtf8()), key);
        QString decryptedSecure = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[5].toUtf8()), key);

        if (decryptedUsername == inputUsername && decryptedSecure == inputSecure)
        {
            QString newPassHash = QCryptographicHash::hash(ui->lineEdit_Pass->text().toUtf8(), QCryptographicHash::Sha256).toHex();
            fields[3] = newPassHash;
        }

        out << fields.join(',') << "\n";
    }

    input_file.close();
    output_file.close();

    input_file.remove();
    output_file.rename("information.txt");

    QMessageBox::information(this, "Password Reset", "Your password has been successfully reset!");
    this->close();
    mymenu = new menu(this);
    mymenu->show();
}

void ForgetPass::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (background)
    {
        background->setGeometry(0, 0, this->width(), this->height());

        QPixmap pixmap(":/new/image1/image.jpg");
        background->setPixmap(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void ForgetPass::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down)
    {
        emit downPressed();
    }
    else if (event->key() == Qt::Key_Up)
    {
        emit upPressed();
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}
