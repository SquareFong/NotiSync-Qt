#ifndef MESSAGESITEMDELEGATE_H
#define MESSAGESITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QMetaType>

class MessagesItemDelegate : public QStyledItemDelegate
{
public:
    MessagesItemDelegate(QObject *parent = nullptr);

    // painting
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

typedef struct MessagesItemData{
    QString IconPath;
    QString Contact;
    QString Number;
    QString Content;
    QString Time;
} MessagesItemData;

Q_DECLARE_METATYPE(MessagesItemData)
#endif // MESSAGESITEMDELEGATE_H
