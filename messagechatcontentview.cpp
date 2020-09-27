#include "messagechatcontentview.h"

MessageChatContentView::MessageChatContentView(QWidget *parent) : QWidget(parent)
{
    chatView = new QVBoxLayout();

    title = new QHBoxLayout();
    contact = new QLabel("test contact");
    deleteChat = new QPushButton();
    deleteChat->setFixedWidth(deleteChat->height());
    title->addWidget(contact);
    title->addWidget(deleteChat);
    chatView->addLayout(title);

    chatContent = new QListView();



    setLayout(chatView);
}
