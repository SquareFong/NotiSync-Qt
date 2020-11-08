#ifndef MESSAGESITEMDELEGATE_H
#define MESSAGESITEMDELEGATE_H

#include <QMetaType>
#include <QStyledItemDelegate>

class MessagesItemDelegate : public QStyledItemDelegate {
public:
    MessagesItemDelegate(QObject* parent = nullptr);
    // painting
    void paint(QPainter* painter,
        const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem& option,
        const QModelIndex& index) const Q_DECL_OVERRIDE;
};

typedef struct MessagesBriefData {
    QString IconPath;
    QString Contact;
    QString Number;
    QString Content;
    QString Time;
} MessagesBriefData;

Q_DECLARE_METATYPE(MessagesBriefData)
#endif // MESSAGESITEMDELEGATE_H
