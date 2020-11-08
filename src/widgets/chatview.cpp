#include "chatview.h"

ChatView::ChatView(QWidget* parent)
    : QWidget(parent)
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

    mainLayout->setStretchFactor(title, 1);
    mainLayout->setStretchFactor(chatContent, 5);
    mainLayout->setStretchFactor(inputArea, 2);

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
