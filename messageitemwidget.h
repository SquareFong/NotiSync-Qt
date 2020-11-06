#ifndef MESSAGEITEMWIDGET_H
#define MESSAGEITEMWIDGET_H

#include <QDebug>
#include <QMetaObject>
#include <QStyledItemDelegate>
#include <QWidget>

typedef struct MessageItemData {
    int messageDirection; //描述消息谁发的，-1:别人 1:我 0:不显示
    QString messageContent;
    time_t messageTime;
} MessageItemData;

Q_DECLARE_METATYPE(MessageItemData)

class MessageItemWidget : public QWidget {
    Q_OBJECT
public:
    void resizeEvent(QResizeEvent* event)
    {
        Q_UNUSED(event);
        qDebug() << "MessageItemWidget" << width() << height();
        genPaintRects();
    }

    explicit MessageItemWidget(QWidget* parent = nullptr);
    void setItemData(MessageItemData data);
    QSize sizeWidget;
    QSize getBorderSize() const;
signals:

private:
    QRect m_borderRect;
    QRect m_contentRect;
    QRect m_timeRect;
    unsigned m_margin;
    QSize m_bordersize;

    MessageItemData m_itemData;
    int m_direction;
    QString m_content;
    QString m_date;

    void genPaintRects();
    QSize genBorderSize(int contentWidth);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif // MESSAGEITEMWIDGET_H
