#ifndef MAINVIEWPHONENOTIFICATIONS_H
#define MAINVIEWPHONENOTIFICATIONS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>

class PhoneNotifications : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneNotifications(QWidget *parent = nullptr);
    ~PhoneNotifications();

public slots:
    //清空消息列表
    void clear(){
        notificationList->clear();
    }

signals:

private:
    QHBoxLayout *header;
    QVBoxLayout *mainLayout;
    QListWidget *notificationList;
};

#endif // MAINVIEWPHONENOTIFICATIONS_H
