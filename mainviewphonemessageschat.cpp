#include "mainviewphonemessageschat.h"
#include "messagechatcontentmodel.h"
//短信页面的详细页面
//分别为默认界面、新建对话界面和对话界面
PhoneMessagesChat::PhoneMessagesChat(QWidget *parent) : QWidget(parent)
{
    stacklayout = new QStackedLayout();

    singleChatView = new QVBoxLayout();
    singleChatViewTitle = new QHBoxLayout();
    singleChatViewTitle->addWidget(new QLabel("Test Title"));
    singleChatViewTitle->addWidget(new QPushButton("test Del"));
    singleChatView->addLayout(singleChatViewTitle);

    singleChatContent = new QListView();
    MessageChatContentModel *m = new MessageChatContentModel();
    singleChatContent->setModel(m);
    m->populate();

//    QStandardItemModel *model = new QStandardItemModel();
//    singleChatContent->setModel(model);

//    QStandardItem *item1 = new QStandardItem("abcsdfasdfasdfasdfasdf");
//    QStandardItem *item2 = new QStandardItem("abc");
//    QStandardItem *item3 = new QStandardItem("abc");
//    QStandardItem *item4 = new QStandardItem("abc");
//    model->appendRow(item1);
//    model->appendRow(item2);
//    model->appendRow(item3);
//    model->appendRow(item4);

    singleChatView->addWidget(singleChatContent);
//    stacklayout->addWidget(new QLabel("请确保您的手机连接到网络\n"
//                                      "Android 信息网页版需要与您的手机搭配使用，"
//                                      "以便您在计算机上\n发送和接收信息。"
//                                      "要减少数据流量消耗，请将手机连接到\n WLAN。"));
    QWidget *tmp = new QWidget();
    tmp->setLayout(singleChatView);
    stacklayout->addWidget(tmp);
    setLayout(stacklayout);

    //item1->setTextAlignment(Qt::AlignRight);

}
