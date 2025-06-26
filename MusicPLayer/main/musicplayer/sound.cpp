#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_volum_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
    ui->volumlabel->setText(QString("%1%").arg(value));
}
/*
void musicplayerpage::processBuffer()
{
    QAudioBuffer buffer = decoder->read();
    if (!buffer.isValid())
        return;

    auto data = buffer.constData<qint16>();
    int samples = buffer.sampleCount();

    qDebug() << "Decoding buffer with samples:" << samples;

    for (int i = 0; i < samples; ++i)
    {
        audioSamples.append(data[i]);
    }

    qDebug() << "Total samples collected:" << audioSamples.size();
}

void musicplayerpage::updateVisualizer()
{
    QVector<int> levels;

    for (int i = 0; i < 20; ++i)
    {
        int value = QRandomGenerator::global()->bounded(100);
        levels.append(value);
    }

    visualizerWidget->setLevels(levels);
}*/
