#include "forgetpass.h"
#include "ui_forgetpass.h"
#include "encryption.h"
#include <QFont>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QPixmap>
#include <QShortcut>

ForgetPass::ForgetPass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgetPass)
{
    ui->setupUi(this);
    this->setWindowTitle("Recovery Page");

    background = new QLabel(this);
    background->lower();
    QFont font("Arial", 12, QFont::Bold);
    this->setFont(font);
    ui->pushButton_Done->setFont(font);
    ui->pushButton_back->setFont(font);

    // Connect return pressed signals
    connect(ui->lineEdit_Pass, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_confPass, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_secure, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);
    connect(ui->lineEdit_username, &QLineEdit::returnPressed, this, &ForgetPass::on_pushButton_Done_clicked);

    // Navigation shortcuts
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

    // ESC shortcut
    QShortcut *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    escShortcut->setContext(Qt::ApplicationShortcut);
    connect(escShortcut, &QShortcut::activated, this, &ForgetPass::on_pushButton_back_clicked);
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
    // First validate inputs
    if (ui->lineEdit_username->text().isEmpty() ||
        ui->lineEdit_secure->text().isEmpty() ||
        ui->lineEdit_Pass->text().isEmpty() ||
        ui->lineEdit_confPass->text().isEmpty())
    {
        QMessageBox::warning(this, "Information Error", "The form is not complete");
        return;
    }

    if (ui->lineEdit_Pass->text() != ui->lineEdit_confPass->text())
    {
        QMessageBox::warning(this, "Password Error", "The password doesn't match");
        return;
    }

    // Open the file
    QFile file("information.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this, "File Error", "Cannot open information file");
        return;
    }

    QTextStream in(&file);
    QStringList lines;
    bool found = false;
    char key = 0x5A;

    // Read all lines and find the matching user
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() >= 6)
        {
            QString decryptedUsername = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[2].toUtf8()), key);
            QString decryptedSecure = simpleXOREncryptDecrypt(QByteArray::fromHex(fields[5].toUtf8()), key);

            if (decryptedUsername == ui->lineEdit_username->text() &&
                decryptedSecure == ui->lineEdit_secure->text())
            {
                // Update the password hash
                fields[3] = QCryptographicHash::hash(ui->lineEdit_Pass->text().toUtf8(), QCryptographicHash::Sha256).toHex();
                line = fields.join(',');
                found = true;
            }
        }
        lines.append(line);
    }

    file.close();

    if (!found)
    {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or secure code.");
        return;
    }

    // Write the updated data back to the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QMessageBox::critical(this, "File Error", "Cannot open information file for writing");
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines)
    {
        out << line << "\n";
    }

    file.close();

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
