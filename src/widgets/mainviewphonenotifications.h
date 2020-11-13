#ifndef MAINVIEWPHONENOTIFICATIONS_H
#define MAINVIEWPHONENOTIFICATIONS_H

#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QWidget>

#include "notificationitemdelegate.h"
#include "src/core/notisyncclient.h"

/*详情页（mainView）的1号页面*/

class PhoneNotifications : public QWidget {
    Q_OBJECT

public:
    explicit PhoneNotifications(NotiSyncClient* NotiSyncClient, QWidget* parent = nullptr);
    ~PhoneNotifications();

public slots:
    //清空消息列表
    void clear()
    {
        //notificationList->clear();
        pModel->clear();
    }

signals:

private:
    QHBoxLayout* header;
    QVBoxLayout* mainLayout;
    QListView* notificationList;
    QStandardItemModel* pModel;
    NotiSyncClient* const nsc;
};

#endif // MAINVIEWPHONENOTIFICATIONS_H
