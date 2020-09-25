#include "mainviewphonemessages.h"

PhoneMessages::PhoneMessages(QWidget *parent) :
    QWidget(parent)
{
    //左边部分，开始
    messagesListLayout = new QVBoxLayout();

    QLabel *title = new QLabel("Messages");
    messagesListLayout->addWidget(title);

    //lastUpdate = new QLabel();
    //UpdateLastUpdate();
    //messagesListLayout->addWidget(lastUpdate);

    newMessage = new QPushButton("New Message");
    messagesListLayout->addWidget(newMessage);

    messagesList = new QListView();
    pMessageListModel = new QStandardItemModel();

    MessagesItemDelegate *pItemDelegate = new MessagesItemDelegate();
    //插入测试数据
    MessagesItemData itemData{
        ":/Icons/defaultAppLogo",
        "test Contact",
        "10086",
        "一条测试信息，看看这玩意能显示多长的文本，啦啦啦啦啦啦啦啦啦",
        "等一个星期三"
    };
    QStandardItem *pItem = new QStandardItem;
    pItem->setEditable(false);
    pItem->setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
    pMessageListModel->appendRow(pItem);

    messagesList->setItemDelegate(pItemDelegate);
    messagesList->setModel(pMessageListModel);
    messagesListLayout->addWidget(messagesList);
    //左边部分，结束

    //右边部分，开始
    messagesContentLayout = new QVBoxLayout();
    messagesContentLayout->addWidget(new QListView());
    //右边部分，结束

    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(messagesListLayout);
    mainLayout->addLayout(messagesContentLayout);

    setLayout(mainLayout);
}

PhoneMessages::~PhoneMessages()
{
}
