#ifndef MESSAGECHATCONTENTMODEL_H
#define MESSAGECHATCONTENTMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <ctime>
#include <QMetaObject>
typedef struct ContentItem {
    int messageDirection; //描述消息谁发的，-1:别人 1:我
    QString messageContent;
    time_t messageTime;
} ContentItem;

Q_DECLARE_METATYPE(ContentItem)

class MessageChatContentModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MessageChatContentModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate();
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
private:
    QList<ContentItem> items;
};

#endif // MESSAGECHATCONTENTMODEL_H
