#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsRectItem>

class Visualizer : public QGraphicsView {
    Q_OBJECT
public:
    Visualizer(QWidget *parent = nullptr);
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    QVector<qreal> bars;
    QVector<QColor> colors;
    void generateRandomBars();
};

#endif // VISUALIZER_H
