#ifndef NOTIFICATIONITEMDELEGATE_H
#define NOTIFICATIONITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QMetaType>

class NotificationItemDelegate : public QStyledItemDelegate
{
public:
    NotificationItemDelegate(QObject *parent = nullptr);

    // painting
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

typedef struct NotificationItemData{
    QString IconPath;
    QString AppName;
    QString Content;
} NotificationItemData;

Q_DECLARE_METATYPE(NotificationItemData)

#endif // NOTIFICATIONITEMDELEGATE_H
