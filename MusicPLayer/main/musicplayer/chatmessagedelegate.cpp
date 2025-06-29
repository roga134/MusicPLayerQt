#include "chatmessagedelegate.h"
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QTextOption>

ChatMessageDelegate::ChatMessageDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ChatMessageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    // Get style from item data
    QString style = index.data(Qt::UserRole).toString();

    painter->save();

    // Apply custom style
    if (!style.isEmpty()) {
        QRect rect = opt.rect.adjusted(2, 2, -2, -2);

        // Determine bubble color based on alignment
        QColor bubbleColor = (index.data(Qt::TextAlignmentRole).toInt() & Qt::AlignRight) ?
                                 QColor(173,216,230) :  // Light green for my messages
                                 QColor(255, 255, 255);   // White for others' messages

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(bubbleColor));
        painter->drawRoundedRect(rect, 12, 12);

        // Add border for others' messages
        if (!(index.data(Qt::TextAlignmentRole).toInt() & Qt::AlignRight)) {
            painter->setPen(QColor(229, 229, 234));
            painter->setBrush(Qt::NoBrush);
            painter->drawRoundedRect(rect, 12, 12);
        }
    }

    // Draw text
    QTextOption textOption;
    textOption.setAlignment(static_cast<Qt::Alignment>(index.data(Qt::TextAlignmentRole).toInt()));
    painter->setPen(opt.palette.text().color());
    painter->drawText(opt.rect.adjusted(8, 5, -8, -5),
                      opt.text, textOption);

    painter->restore();
}

QSize ChatMessageDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    return QSize(size.width(), size.height() + 10); // Add some padding
}
