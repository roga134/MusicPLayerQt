#include "ClickableRectItem.h"

void ClickableGraphicsView::mousePressEvent(QMouseEvent *event)
{
    emit clicked(event->pos());
    QGraphicsView::mousePressEvent(event);
}
