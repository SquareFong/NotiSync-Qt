#include "messagechatcontentmodel.h"

MessageChatContentModel::MessageChatContentModel()
{

}

int MessageChatContentModel::rowCount(const QModelIndex &parent) const{
    return items.size();
}

int MessageChatContentModel::columnCount(const QModelIndex &parent) const{
    return 1;
}

QVariant MessageChatContentModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    if ( role == Qt::DisplayRole)
    {
        return items[index.row()].messageContent;
    }
    return QVariant();
}

void MessageChatContentModel::populate(){
    beginResetModel();
    items.clear();
    time_t t;
    time(&t);
    items.append(ContentItem{-1, "test1jdfhalksjdfhlakjsdhflkjashdlfkjhaslkdjfklasdhflkjahslkdfjhsldkjh", t});
    items.append(ContentItem{1, "test1", t+1});
    items.append(ContentItem{-1, "test1", t+2});
    items.append(ContentItem{1, "test1", t+3});
    endResetModel();
}

QModelIndex MessageChatContentModel::index(int row, int column,
                  const QModelIndex &parent)const{

    return createIndex(row, column);
}

QModelIndex MessageChatContentModel::parent(const QModelIndex &child)const{
    return QModelIndex();
}
