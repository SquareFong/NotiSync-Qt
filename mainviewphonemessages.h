#ifndef MAINVIEWPHONEMESSAGES_H
#define MAINVIEWPHONEMESSAGES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStackedLayout>
#include <ctime>

#include "messagesitemdelegate.h"

namespace Ui {
class PhoneMessages;
}

class PhoneMessages : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneMessages(QWidget *parent = nullptr);
    ~PhoneMessages();

    void UpdateLastUpdate(){
        lastUpdateTime = time(0);
        lastUpdate->setText(QString("Last update time: ") + std::ctime(&lastUpdateTime));
    }
private:
    QHBoxLayout *mainLayout;

    //左侧短信列表信息
    QVBoxLayout *messagesListLayout;
    QLabel *lastUpdate;
    QPushButton * newMessage;
    time_t lastUpdateTime;

    QListView *messagesList;
    QStandardItemModel *pMessageListModel;

    //右侧短信详情
    QVBoxLayout *messagesContentLayout;

};

#endif // MAINVIEWPHONEMESSAGES_H
