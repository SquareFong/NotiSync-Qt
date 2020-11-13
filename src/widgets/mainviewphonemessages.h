#ifndef MAINVIEWPHONEMESSAGES_H
#define MAINVIEWPHONEMESSAGES_H

#include <QHBoxLayout>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QStackedLayout>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QWidget>
#include <ctime>

#include "chatview.h"
#include "messagesitemdelegate.h"
#include "src/core/notisyncclient.h"

/*详情页（mainView）的2号页面*/

namespace Ui {
class PhoneMessages;
}

class PhoneMessages : public QWidget {
    Q_OBJECT

public:
    explicit PhoneMessages(NotiSyncClient* NotiSyncClient, QWidget* parent = nullptr);
    ~PhoneMessages();

    void UpdateLastUpdate()
    {
        lastUpdateTime = time(0);
        lastUpdate->setText(QString("Last update time: ") + std::ctime(&lastUpdateTime));
    }

private:
    QHBoxLayout* mainLayout;

    //左侧短信列表信息
    QVBoxLayout* messagesListLayout;
    QLabel* lastUpdate;
    QPushButton* newMessage;
    time_t lastUpdateTime;

    QListView* messagesList;
    QStandardItemModel* pMessageListModel;

    //右侧短信详情
    //QVBoxLayout *messageChatLayout;
    ChatView* messageSingleChat; //单个短信对话
    NotiSyncClient* const nsc;
};

#endif // MAINVIEWPHONEMESSAGES_H
