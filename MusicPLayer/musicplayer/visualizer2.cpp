#include "visualizer2.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

Visualizer2::Visualizer2(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_OpaquePaintEvent);

    particles.resize(50); // تعداد ذرات
    initParticles();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        updateParticles();
        update();
    });
}

void Visualizer2::initParticles()
{
    for (auto& p : particles) {
        p.position = QPointF(
            QRandomGenerator::global()->bounded(width()),
            QRandomGenerator::global()->bounded(height())
            );
        p.velocity = QPointF(
            QRandomGenerator::global()->bounded(2.0) - 1.0,
            QRandomGenerator::global()->bounded(2.0) - 1.0
            );
        p.color = QColor::fromHsv(
            QRandomGenerator::global()->bounded(360),
            150 + QRandomGenerator::global()->bounded(100),
            200 + QRandomGenerator::global()->bounded(55)
            );
        p.radius = 5 + QRandomGenerator::global()->bounded(10);
    }
}

void Visualizer2::start()
{
    if(ispaused)
    {
        ispaused =false;
    }
    timer->start(30);

}

void Visualizer2::stop()
{
    timer->stop();
    ispaused=true;
}

void Visualizer2::updateParticles()
{
    for (auto& p : particles) {
        p.position += p.velocity;

        // برخورد با دیوارها
        if (p.position.x() < 0 || p.position.x() > width()) {
            p.velocity.setX(-p.velocity.x());
        }
        if (p.position.y() < 0 || p.position.y() > height()) {
            p.velocity.setY(-p.velocity.y());
        }
    }
}

void Visualizer2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), QColor(100, 203, 203));

    // رسم ذرات
    for (const auto& p : particles) {
        QRadialGradient grad(p.position, p.radius);
        grad.setColorAt(0, p.color.lighter(150));
        grad.setColorAt(1, Qt::transparent);

        painter.setPen(Qt::NoPen);
        painter.setBrush(grad);
        painter.drawEllipse(p.position, p.radius, p.radius);
    }
}

void Visualizer2::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    initParticles();
}
