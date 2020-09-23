#include "mainviewphonenotifications.h"
#include <QPushButton>
#include <QListWidgetItem>

PhoneNotifications::PhoneNotifications(QWidget *parent) :
    QWidget(parent)
{
    //头部标题
    header = new QHBoxLayout();
    header->addWidget(new QLabel("Notifications"));
    QPushButton *buttonCLear = new QPushButton("Clear");
    buttonCLear->setMaximumWidth(100);
    connect(buttonCLear, &QPushButton::released, this, &PhoneNotifications::clear);
    header->addWidget(buttonCLear);

    //通知列表
    notificationList = new QListWidget();
    //notificationList->setFlow(QListView::LeftToRight);
    //notificationList->setProperty("isWrapping", QVariant(true));
    notificationList->setWordWrap(true);
    notificationList->setTextElideMode(Qt::ElideLeft);
    /**测试信息**/
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/Icons/phone call"), QString("text"), notificationList);
    //item->setTextAlignment()
    notificationList->addItem("这是一条中文测试，测试自动换行是否有效。。。。。");
    notificationList->addItem("test2:34567865433466543456787654346787654456");
    notificationList->addItem("test3:ghuikmmjuygvgkmvgbvghmbghunbvghjabsdhjfnbhjakwmenfj");

    //设置主页面
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(header);
    mainLayout->addWidget(notificationList);

    setLayout(mainLayout);

}

PhoneNotifications::~PhoneNotifications()
{
}
