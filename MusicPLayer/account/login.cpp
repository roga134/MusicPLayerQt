#include "login.h"
#include "ui_login.h"
#include "encryption.h"
#include <QFont>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QPixmap>
#include <QLineEdit>

LogIn::LogIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In Page");

    background = new QLabel(this);
    background->lower();    
    QFont font("Arial" , 12 , QFont::Bold);
    this->setFont(font);
    ui->pushButton_back->setFont(font);
    ui->pushButton_enter->setFont(font);

    connect(ui->lineEdit_pass, &QLineEdit::returnPressed, this, &LogIn::on_pushButton_enter_clicked);
    connect(ui->lineEdit_username, &QLineEdit::returnPressed, this, &LogIn::on_pushButton_enter_clicked);

    connect(this, &LogIn::downPressed, this, [=]() {
        if (ui->lineEdit_username->hasFocus())
            ui->lineEdit_pass->setFocus();
        else if (ui->lineEdit_pass->hasFocus())
            ui->pushButton_enter->setFocus();
    });

    connect(this, &LogIn::upPressed, this, [=]() {
        if (ui->lineEdit_pass->hasFocus())
            ui->lineEdit_username->setFocus();
    });

}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_back_clicked()
{
    this->close();
    mymenu = new menu(this);
    mymenu->show();
}

void LogIn::on_pushButton_enter_clicked()
{
    QFile file("information.txt");

    try {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("can not open information file for reading");
        }
    }
    catch (const std::exception& e)
    {
        QMessageBox::critical(this, "File Error", e.what());
        return ;
    }


    QTextStream in(&file);
    char key = 0x5A;

    QString inputUsername = ui->lineEdit_username->text();
    QString inputPassHash = QCryptographicHash::hash(ui->lineEdit_pass->text().toUtf8(), QCryptographicHash::Sha256).toHex();

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        QString encryptedUsername = fields[2];
        QString decryptedUsername = simpleXOREncryptDecrypt(QByteArray::fromHex(encryptedUsername.toUtf8()), key);

        QString storedPassHash = fields[3];

        if (decryptedUsername == inputUsername && storedPassHash == inputPassHash)
        {
            QMessageBox::information(this, "Welcome", "Login Successful");
            QString path = QCoreApplication::applicationDirPath() + "/../musicplayer/musicplayer";
            #ifdef Q_OS_WIN
                path = QCoreApplication::applicationDirPath() +"/../../musicplayer/debug/musicplayer.exe";
            #endif

            QString decryptedFirstName = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[0].toUtf8()), key);
            QString decryptedLastName  = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[1].toUtf8()), key);
            QString decryptedUsername  = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[2].toUtf8()), key);
            QString decryptedEmail     = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[4].toUtf8()), key);

            QStringList arguments;
            arguments << decryptedFirstName << decryptedLastName <<decryptedUsername << decryptedEmail;

            QProcess::startDetached(path, arguments);

            file.close();
            qApp->quit();
            QCoreApplication::exit(0);
            this->close();
            return;
        }
    }

    file.close();
    QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
}

void LogIn::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (background)
    {
        background->setGeometry(0, 0, this->width(), this->height());

        QPixmap pixmap(":/new/image1/image.jpg");
        background->setPixmap(pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void LogIn::keyPressEvent(QKeyEvent *event)
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
