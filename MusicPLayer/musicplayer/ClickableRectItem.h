#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>

class ClickableGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;

signals:
    void clicked(QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *event) override ;
};

#endif
