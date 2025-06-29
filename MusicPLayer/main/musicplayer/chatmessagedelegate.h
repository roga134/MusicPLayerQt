#ifndef CHATMESSAGEDELEGATE_H
#define CHATMESSAGEDELEGATE_H

#include <QStyledItemDelegate>

class ChatMessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatMessageDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

#endif // CHATMESSAGEDELEGATE_H
