#include "VisualizerWidget.h"
#include <QPainter>
#include <QBrush>

VisualizerWidget::VisualizerWidget(QWidget *parent)
    : QWidget(parent)
{
}

void VisualizerWidget::setLevels(const QVector<int> &levels)
{
    m_levels = levels;
    update();
}

void VisualizerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int barCount = m_levels.size();
    if (barCount == 0)
        return;

    int barWidth = width() / barCount;
    int maxHeight = height();

    painter.setBrush(QBrush(Qt::green));
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < barCount; ++i)
    {
        int barHeight = (m_levels[i] * maxHeight) / 100;
        int x = i * barWidth;
        int y = maxHeight - barHeight;

        painter.drawRect(x, y, barWidth - 2, barHeight);
    }
}
