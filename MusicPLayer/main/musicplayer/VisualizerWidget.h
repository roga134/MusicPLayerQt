#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H

#include <QWidget>
#include <QVector>

class VisualizerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VisualizerWidget(QWidget *parent = nullptr);

    void setLevels(const QVector<int> &levels);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> m_levels;
};

#endif
