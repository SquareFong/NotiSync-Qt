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
    MessagesBriefData itemData{
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
    messageSingleChat = new ChatView();
    time_t t;
    time(&t);
    MessageItemData item{-1, "哈哈哈哈哈哈哈哈哈", t};
    messageSingleChat->pushContent(item);
    item.messageDirection = 1;
    messageSingleChat->pushContent(item);
    item.messageContent = QString("我就测试一下这玩意到底能显示多少字开始自动换行, 阿三客户端分量卡及山大路分开,阿克苏觉得很烦拉卡就是多了封口机和拉跨技术鉴定还复来卡及士大夫");
    messageSingleChat->pushContent(item);
    //右边部分，结束

    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(messagesListLayout);
    mainLayout->addWidget(messageSingleChat);
    //mainLayout->addWidget(messagesChatLayout);
    mainLayout->setStretchFactor(messagesListLayout, 2);
    mainLayout->setStretchFactor(messageSingleChat, 3);

    setLayout(mainLayout);
}

PhoneMessages::~PhoneMessages()
{
}
