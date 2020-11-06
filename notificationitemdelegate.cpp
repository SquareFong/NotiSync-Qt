#include "notificationitemdelegate.h"

#include <QPainter>
#include <QPainterPath>

NotificationItemDelegate::NotificationItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void NotificationItemDelegate::paint(QPainter* painter,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole + 1);
        NotificationItemData itemData = var.value<NotificationItemData>();

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);

        //绘制边框
        QPainterPath path;
        int marginValue = 6;
        path.addRoundedRect(rect.topLeft().x() + marginValue,
            rect.topLeft().y() + marginValue,
            rect.width() - marginValue * 2,
            rect.height() - marginValue * 2,
            8, 8);
        // 鼠标悬停或者选中时改变背景色
        painter->setPen(QColor(0, 0, 0, 0));
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setBrush(QColor("#ebeced"));
        } else {
            painter->setBrush(QColor(255, 255, 255, 255));
        }
        painter->drawPath(path);

        // 绘制应用图标、标题、内容的区域
        QRectF iconRect = QRect(rect.left() + marginValue * 2, rect.top() + marginValue * 2,
            30, 30);
        QRectF titleRect = QRect(iconRect.right() + marginValue, iconRect.top(),
            rect.width() - 10 - iconRect.width(), 20);
        QRectF contentRect = QRectF(titleRect.left(), titleRect.bottom() + marginValue,
            rect.width() - marginValue * 4 - iconRect.width(), rect.height() - marginValue * 2 - titleRect.height());

        painter->drawImage(iconRect, QImage(itemData.IconPath));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Noto Mono", 15));
        painter->drawText(titleRect, itemData.AppName);

        QFontMetrics fm = painter->fontMetrics();
        QString content = fm.elidedText(itemData.Content,
            Qt::ElideRight,
            contentRect.width(),
            Qt::TextShowMnemonic);
        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Noto Mono", 15));
        painter->drawText(contentRect, content);

        painter->restore();
    }
}

QSize NotificationItemDelegate::sizeHint(const QStyleOptionViewItem& option,
    const QModelIndex& index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 86);
}
