#include "chatview.h"

ChatView::ChatView(NotiSyncClient* NotiSyncClient, QWidget* parent)
    : QWidget(parent)
    , nsc(NotiSyncClient)
{
    mainLayout = new QVBoxLayout();

    contactName = new QLabel("test contact");
    deleteChat = new QPushButton("Del");
    QHBoxLayout* title = new QHBoxLayout();
    title->addWidget(contactName);
    title->addWidget(deleteChat);
    mainLayout->addLayout(title);

    chatContent = new QListWidget();
    mainLayout->addWidget(chatContent);

    inputArea = new QTextEdit();
    mainLayout->addWidget(inputArea);

    sendMessage = new QPushButton("Send");
    mainLayout->addWidget(sendMessage);
    connect(sendMessage, &QPushButton::clicked, this, &ChatView::sendMessageClicked);

    mainLayout->setStretchFactor(title, 1);
    mainLayout->setStretchFactor(chatContent, 5);
    mainLayout->setStretchFactor(inputArea, 2);
    mainLayout->setStretchFactor(sendMessage, 1);

    setLayout(mainLayout);
}

void ChatView::pushContent(MessageItemData data)
{
    QListWidgetItem* item = new QListWidgetItem(chatContent);
    MessageItemWidget* message = new MessageItemWidget(chatContent);
    message->setFixedWidth(width());
    message->setItemData(data);
    item->setSizeHint(message->sizeWidget);
    chatContent->setItemWidget(item, message);
}
