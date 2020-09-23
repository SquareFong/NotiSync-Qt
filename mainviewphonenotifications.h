#ifndef MAINVIEWPHONENOTIFICATIONS_H
#define MAINVIEWPHONENOTIFICATIONS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QStandardItem>

#include "notificationitemdelegate.h"

class PhoneNotifications : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneNotifications(QWidget *parent = nullptr);
    ~PhoneNotifications();

public slots:
    //清空消息列表
    void clear(){
        //notificationList->clear();
        pModel->clear();
    }

signals:

private:
    QHBoxLayout *header;
    QVBoxLayout *mainLayout;
    QListView *notificationList;
    QStandardItemModel *pModel;
};

#endif // MAINVIEWPHONENOTIFICATIONS_H
