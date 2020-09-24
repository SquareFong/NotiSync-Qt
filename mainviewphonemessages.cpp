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

    //暂时借用Notification的delagate。
    NotificationItemDelegate *pItemDelegate = new NotificationItemDelegate();

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
