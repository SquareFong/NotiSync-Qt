#include "mainviewphonemessageschat.h"
//短信页面的详细页面
//分别为默认界面、新建对话界面和对话界面
PhoneMessagesChat::PhoneMessagesChat(QWidget *parent) : QWidget(parent)
{
    stacklayout = new QStackedLayout();

    stacklayout->addWidget(new QLabel("请确保您的手机连接到网络\n"
                                      "Android 信息网页版需要与您的手机搭配使用，"
                                      "以便您在计算机上\n发送和接收信息。"
                                      "要减少数据流量消耗，请将手机连接到\n WLAN。"));

    setLayout(stacklayout);
}
