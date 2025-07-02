#ifndef VISUALIZER2_H
#define VISUALIZER2_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QColor>

class Visualizer2 : public QWidget
{
    Q_OBJECT
public:
    explicit Visualizer2(QWidget *parent = nullptr);
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    struct Particle {
        QPointF position;
        QPointF velocity;
        QColor color;
        float radius;
    };

    QTimer *timer;
    QVector<Particle> particles;
    void initParticles();
    void updateParticles();
    bool ispaused;
};

#endif // VISUALIZER2_H
