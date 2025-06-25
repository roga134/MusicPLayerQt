#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_volum_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
    ui->volumlabel->setText(QString("%1%").arg(value));
}

