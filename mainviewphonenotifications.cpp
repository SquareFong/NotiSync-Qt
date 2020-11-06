#include "mainviewphonenotifications.h"

#include <QListWidgetItem>
#include <QPushButton>

PhoneNotifications::PhoneNotifications(QWidget* parent)
    : QWidget(parent)
{
    //头部标题
    header = new QHBoxLayout();
    header->addWidget(new QLabel("Notifications"));
    QPushButton* buttonCLear = new QPushButton("Clear");
    buttonCLear->setMaximumWidth(100);
    connect(buttonCLear, &QPushButton::released, this, &PhoneNotifications::clear);
    header->addWidget(buttonCLear);

    notificationList = new QListView();
    pModel = new QStandardItemModel();

    //插入测试数据
    NotificationItemData itemdata { ":/Icons/defaultAppLogo",
        "test APP",
        "test Content:这是一条中文测试，测试自动换行是否有效。。。。。长度不够，凑个数" };

    QStandardItem* pItem = new QStandardItem;
    pItem->setEditable(false);
    pItem->setData(QVariant::fromValue(itemdata), Qt::UserRole + 1);

    pModel->appendRow(pItem);
    NotificationItemDelegate* pItemDelegate = new NotificationItemDelegate();
    notificationList->setItemDelegate(pItemDelegate);
    notificationList->setModel(pModel);

    //设置主页面
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(header);
    mainLayout->addWidget(notificationList);

    setLayout(mainLayout);
}

PhoneNotifications::~PhoneNotifications()
{
}
