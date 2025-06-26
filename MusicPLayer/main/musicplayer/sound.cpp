#include "musicplayerpage.h"
#include "ui_musicplayerpage.h"

void musicplayerpage::on_volum_valueChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
    ui->volumlabel->setText(QString("%1%").arg(value));
}

void musicplayerpage::processBuffer()
{
    if (!decoder->bufferAvailable())
        return;

    QAudioBuffer buffer = decoder->read();
    if (buffer.format().sampleFormat() != QAudioFormat::Int16)
        return;

    const qint16 *data = buffer.constData<qint16>();
    int sampleCount = buffer.sampleCount();

    int bandCount = 5;
    std::vector<double> bands(bandCount, 0.0);

    for (int i = 0; i < sampleCount; ++i)
    {
        int bandIndex = (i * bandCount) / sampleCount;
        bands[bandIndex] += std::abs(data[i]);
    }

    for (int i = 0; i < bandCount; ++i)
        bands[i] /= sampleCount / bandCount;

    currentBands.clear();
    for (double val : bands)
        currentBands.append(val);
    updateVisualizer();
}

void musicplayerpage::updateVisualizer()
{
    int maxHeight = ui->graphicsView->viewport()->height();
    int bandCount = currentBands.size();

    for (int i = 0; i < bars.size() && i < bandCount; ++i)
    {
        int scaledHeight = static_cast<int>(currentBands[i] / 200.0);
        if (scaledHeight > maxHeight)
            scaledHeight = maxHeight;

        bars[i]->setRect(bars[i]->rect().x(),
                         maxHeight - scaledHeight,
                         bars[i]->rect().width(),
                         scaledHeight);
    }

    scene->update();
}

void musicplayerpage::setupVisualizerBars()
{
    scene->clear();
    bars.clear();

    int viewWidth = ui->graphicsView->viewport()->width();
    int viewHeight = ui->graphicsView->viewport()->height();

    scene->setSceneRect(0, 0, viewWidth, viewHeight);

    int barCount = 20;
    int spacing = 10;
    int barWidth = (viewWidth - (barCount - 1) * spacing) / barCount;
    int barHeight = 10;
    int baseY = viewHeight - barHeight;

    int startX = 0;
    for (int i = 0; i < barCount; i++) {
        QGraphicsRectItem *bar = scene->addRect(startX, baseY, barWidth, barHeight,
                                                QPen(Qt::black), QBrush(Qt::blue));
        bars.append(bar);
        startX += barWidth + spacing;
    }
}

void musicplayerpage::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    setupVisualizerBars();
}
