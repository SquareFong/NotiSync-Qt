#include "messagesitemdelegate.h"

#include <QPainter>
#include <QPainterPath>

MessagesItemDelegate::MessagesItemDelegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}

void MessagesItemDelegate::paint(QPainter *painter,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole+1);
        MessagesItemData itemData = var.value<MessagesItemData>();

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //绘制边框
        QPainterPath path;
        path.addRect(rect.topLeft().x(),
                     rect.topLeft().y(),
                     rect.width(),
                     rect.height());
        // 鼠标悬停或者选中时改变背景色
        painter->setPen(QColor(0,0,0,0));
        if(option.state.testFlag(QStyle::State_Selected)){
                   painter->setBrush(QColor("#f1f2f3"));
        }
        else if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setBrush(QColor("#f5f6f7"));
        }
        else {
            painter->setBrush(QColor("#ffffff"));
        }
        painter->drawPath(path);

        // 绘制应用图标、标题、内容的区域
        int iconHeight = rect.height()*5/9;
        int marginValue = rect.height()/12;
        QRectF iconRect = QRect(rect.left()+marginValue * 2, rect.top()+marginValue * 2,
                                iconHeight, iconHeight);
        QRectF titleRect = QRect(iconRect.right() + marginValue * 2, iconRect.top(),
                                 (rect.width()- marginValue * 4 - iconRect.right()) * 3 /4, iconHeight/2);
        QRectF timeRect = QRect(titleRect.right(), titleRect.top(),
                                titleRect.width() / 3, iconHeight/2);
        QRectF contentRect = QRectF(titleRect.left(), titleRect.bottom()+marginValue,
                                    rect.width() - marginValue * 4  - iconRect.right(), iconHeight/2);

        painter->drawImage(iconRect, QImage(itemData.IconPath));

        QFontMetrics fm = painter->fontMetrics();
        QString content = fm.elidedText(itemData.Contact,
                                        Qt::ElideRight,
                                        titleRect.width(),
                                        Qt::TextShowMnemonic);
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Noto Mono", 13));
        painter->drawText(titleRect, content);

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Noto Mono", 13));
        painter->drawText(timeRect, itemData.Time);

        QFontMetrics fm1 = painter->fontMetrics();
        QString content1 = fm1.elidedText(itemData.Content,
                                        Qt::ElideRight,
                                        contentRect.width(),
                                        Qt::TextShowMnemonic);
        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Noto Mono", 13));
        painter->drawText(contentRect, content1);

        painter->restore();
    }
}

QSize MessagesItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 86);
}
