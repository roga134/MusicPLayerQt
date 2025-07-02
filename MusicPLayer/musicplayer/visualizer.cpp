#include "visualizer.h"

Visualizer::Visualizer(QWidget *parent) : QGraphicsView(parent) {
    setScene(new QGraphicsScene(this));
    setRenderHint(QPainter::Antialiasing);
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background: transparent;");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        generateRandomBars();
        viewport()->update();
    });


    bars.resize(20);
    colors.resize(20);


    for (int i = 0; i < colors.size(); ++i) {
        colors[i] = QColor(rand() % 256, rand() % 256, rand() % 256);
    }
}

void Visualizer::start() {
    timer->start(100);
}

void Visualizer::stop() {
    timer->stop();
}

void Visualizer::generateRandomBars() {
    for (int i = 0; i < bars.size(); ++i) {
        bars[i] = (qreal)(rand() % 100) / 100.0;
    }
}

void Visualizer::paintEvent(QPaintEvent *event) {
    qDebug() << "Painting visualizer...";
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = viewport()->rect();
    int barWidth = rect.width() / (bars.size() * 1.5);
    int spacing = barWidth / 2;
    int maxHeight = rect.height() - 20;

    for (int i = 0; i < bars.size(); ++i) {
        int x = spacing + i * (barWidth + spacing);
        int height = maxHeight * bars[i];
        int y = rect.height() - height;

        QLinearGradient gradient(x, y, x + barWidth, y + height);
        gradient.setColorAt(0, colors[i].lighter(150));
        gradient.setColorAt(1, colors[i].darker(150));

        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(x, y, barWidth, height, 3, 3);
    }

    QGraphicsView::paintEvent(event);
}
