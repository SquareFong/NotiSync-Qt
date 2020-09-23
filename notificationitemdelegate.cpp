#include "notificationitemdelegate.h"

#include <QPainter>
#include <QPainterPath>


NotificationItemDelegate::NotificationItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void NotificationItemDelegate::paint(QPainter *painter,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole+1);
        NotificationItemData itemData = var.value<NotificationItemData>();

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //绘制边框
        QPainterPath path;

        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            int marginV = 6;
//            QPointF tl(rect.topLeft().x() + marginV, rect.topLeft().y() + marginV), tr(rect.topRight().x() - marginV, rect.topRight().y() + marginV),
//                    bl(rect.bottomLeft().x() + marginV, rect. bottomLeft().y() - marginV), br(rect.bottomRight().x() - marginV, rect.bottomRight().y() - marginV );
//            path.moveTo(tr);
//            path.lineTo(tl);
//            path.quadTo(tl , tl);
//            path.lineTo(bl);
//            path.quadTo(bl, bl);
//            path.lineTo(br);
//            path.quadTo(br, br);
//            path.lineTo(tr);
//            path.quadTo(tr, tr);
            //painter->setPen(QPen(QColor("#ebeced")));
//            painter->setPen(QPen(QColor("#e3e3e5")));
//            painter->setBrush(QColor("#e3e3e5"));

            path.addRoundedRect(rect.topLeft().x() + marginV,
                                rect.topLeft().y() + marginV,
                                rect.width() - marginV * 2,
                                rect.height() - marginV * 2,
                                8, 8);
            painter->setBrush(QColor("#ebeced"));
            painter->drawPath(path);
        }
//        if (option.state.testFlag(QStyle::State_Selected)) {
//            path.moveTo(rect.topRight());
//            path.lineTo(rect.topLeft());
//            path.quadTo(rect.topLeft(), rect.topLeft());
//            path.lineTo(rect.bottomLeft());
//            path.quadTo(rect.bottomLeft(), rect.bottomLeft());
//            path.lineTo(rect.bottomRight());
//            path.quadTo(rect.bottomRight(), rect.bottomRight());
//            path.lineTo(rect.topRight());
//            path.quadTo(rect.topRight(), rect.topRight());
//            painter->setPen(QPen(QColor("#ebeced")));
//            painter->setBrush(QColor("#ebeced"));
//            painter->drawPath(path);
//        }


        // 绘制应用图标、标题、内容的区域
        int marginValue = 5;
        QRectF iconRect = QRect(rect.left()+marginValue, rect.top()+marginValue,
                                40, 40);
        QRectF titleRect = QRect(iconRect.right()+marginValue, iconRect.top(),
                                 rect.width()-10-iconRect.width(), 20);
        QRectF contentRect = QRectF(titleRect.left(), titleRect.bottom()+marginValue,
                                    rect.width()-10-iconRect.width(), rect.height() - 10 - titleRect.height());

        painter->drawImage(iconRect, QImage(itemData.IconPath));

        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Noto Mono", 15));
        painter->drawText(titleRect, itemData.AppName);

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Noto Mono", 12));
        painter->drawText(contentRect, itemData.Content);
    }
}

QSize NotificationItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 100);
}
