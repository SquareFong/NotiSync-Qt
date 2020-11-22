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

public slots:
    void messageListClicked(const QModelIndex& index)
    {
        QVariant var = index.data(Qt::UserRole + 1);
        MessagesBriefData itemData = var.value<MessagesBriefData>();
        printf("Number: %s\n", itemData.Number.toStdString().c_str());
        vector<Message> singleChat
            = nsc->getSingleChat(itemData.Number.toStdString());

        messageSingleChat->clear();
        if (singleChat.size() != 0) {
            for (auto it = singleChat.rbegin(); it != singleChat.rend(); ++it) {
                int direction = atoi((*it).type.c_str());
                direction = (direction == 1 ? -1 : 1);
                MessageItemData item { direction, (*it).body.c_str(), stol((*it).date) };
                messageSingleChat->pushContent(item);
            }
            messageSingleChat->contactName->setText((itemData.Contact.size() == 0) ? itemData.Number : itemData.Contact);
            messageSingleChat->scrollToButtom();
        } else {
            messageSingleChat->contactName->setText("");
        }
    }

protected:
    void timerEvent(QTimerEvent* event);

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

    int m_timerid;

private:
    void refreshMessageDigest();
};

#endif // MAINVIEWPHONEMESSAGES_H
