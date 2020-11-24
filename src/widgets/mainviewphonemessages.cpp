#include "mainviewphonemessages.h"

#include <QTimerEvent>

void PhoneMessages::refreshMessageDigest()
{
    vector<Message> digest = nsc->getMessageDigest();
    if (digest.size()) {
        pMessageListModel->clear();
        for (auto& item : digest) {
            MessagesBriefData itemData {
                ":/Icons/defaultAppLogo",
                item.name.c_str(),
                item.number.c_str(),
                item.body.c_str(),
                item.date.c_str()
            };
            QStandardItem* pItem = new QStandardItem;
            pItem->setEditable(false);
            pItem->setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
            pMessageListModel->appendRow(pItem);
        }
    }
}

void PhoneMessages::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerid) {
        refreshMessageDigest();
    }
}

PhoneMessages::PhoneMessages(NotiSyncClient* NotiSyncClient, QWidget* parent)
    : QWidget(parent)
    , nsc(NotiSyncClient)
    , m_timerid(startTimer(300))
{
    //左边部分，开始
    messagesListLayout = new QVBoxLayout();

    QLabel* title = new QLabel("Messages");
    messagesListLayout->addWidget(title);

    //lastUpdate = new QLabel();
    //UpdateLastUpdate();
    //messagesListLayout->addWidget(lastUpdate);

    createNewMessage = new QPushButton("New Message");
    messagesListLayout->addWidget(createNewMessage);
    connect(createNewMessage, &QPushButton::clicked, this, &PhoneMessages::createNewMessageClicked);

    messagesList = new QListView();
    pMessageListModel = new QStandardItemModel();

    MessagesItemDelegate* pItemDelegate = new MessagesItemDelegate();
    //插入测试数据
    //    MessagesBriefData itemData {
    //        ":/Icons/defaultAppLogo",
    //        "test Contact",
    //        "10086",
    //        "一条测试信息，看看这玩意能显示多长的文本，啦啦啦啦啦啦啦啦啦",
    //        "等一个星期三"
    //    };
    //    QStandardItem* pItem = new QStandardItem;
    //    pItem->setEditable(false);
    //    pItem->setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
    //    pMessageListModel->appendRow(pItem);

    //    MessagesBriefData itemData1 {
    //        ":/Icons/defaultAppLogo",
    //        "test Contact1",
    //        "10010",
    //        "一条测试信息，看看这玩意能显示多长的文hhhhhhhhhhhhhhhh",
    //        "星期2"
    //    };
    //    QStandardItem* pItem1 = new QStandardItem;
    //    pItem1->setEditable(false);
    //    pItem1->setData(QVariant::fromValue(itemData1), Qt::UserRole + 1);
    //    pMessageListModel->appendRow(pItem1);

    messagesList->setItemDelegate(pItemDelegate);
    messagesList->setModel(pMessageListModel);
    messagesListLayout->addWidget(messagesList);
    connect(messagesList, &QListView::clicked, this, &PhoneMessages::messageListClicked);
    //左边部分，结束

    //右边部分，开始
    messageSingleChat = new ChatView(nsc, this);
    time_t t;
    time(&t);
    //    MessageItemData item { -1, "哈哈哈哈哈哈哈哈哈", t };
    //    messageSingleChat->pushContent(item);
    //    item.messageDirection = 1;
    //    messageSingleChat->pushContent(item);
    //    item.messageContent = QString("我就测试一下这玩意到底能显示多少字开始自动换行, 阿三客户端分量卡及山大路分开,阿克苏觉得很烦拉卡就是多了封口机和拉跨技术鉴定还复来卡及士大夫");
    //    messageSingleChat->pushContent(item);
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
