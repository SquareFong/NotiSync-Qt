#include "mainviewphonenotifications.h"

#include <QListWidgetItem>
#include <QPushButton>
#include <QTimerEvent>
#include <utility>

void PhoneNotifications::refreshView()
{
    vector<Notification> notis = nsc->getNotifications();
    pModel->clear();
    for (auto& item : notis) {
        NotificationItemData itemdata { ":/Icons/defaultAppLogo",
            item.packageName.c_str(),
            item.content.c_str() };
        QStandardItem* pItem = new QStandardItem;
        pItem->setEditable(false);
        pItem->setData(QVariant::fromValue(std::move(itemdata)), Qt::UserRole + 1);
        pModel->appendRow(pItem);
    }
}

void PhoneNotifications::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerid) {
        refreshView();
    }
}
PhoneNotifications::PhoneNotifications(NotiSyncClient* NotiSyncClient, QWidget* parent)
    : QWidget(parent)
    , nsc(NotiSyncClient)
    , m_timerid(startTimer(300))
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
