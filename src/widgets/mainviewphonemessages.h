#ifndef MAINVIEWPHONEMESSAGES_H
#define MAINVIEWPHONEMESSAGES_H

#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMessageBox>
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
            messageSingleChat->setContact((itemData.Contact.size() == 0) ? itemData.Number : itemData.Contact);
            messageSingleChat->scrollToButtom();
        } else {
            messageSingleChat->setContact("");
        }
    }

    void createNewMessageClicked()
    {
        QString title = "NotiSync";
        QString label = "Phone Number";
        QString defaultInput = "";
        QLineEdit::EchoMode echoMode = QLineEdit::Normal;
        bool ok = false;
        while (true) {
            QString text = QInputDialog::getText(this, title, label,
                echoMode, defaultInput, &ok);
            if (ok) {
                if (!text.isEmpty()) {
                    bool isLong = false;
                    unsigned long long num = text.toULongLong(&isLong);
                    if (isLong) {
                        //TODO 找对话，如果没有，新建对话
                        messageSingleChat->clear();
                        messageSingleChat->setContact(text);

                        int rows = pMessageListModel->rowCount();
                        int columns = pMessageListModel->columnCount();
                        for (int i = 0; i < rows; ++i) {
                            QStandardItem* item = pMessageListModel->item(i);
                            QVariant var = item->data(Qt::UserRole + 1);
                            MessagesBriefData itemData = var.value<MessagesBriefData>();
                            if (itemData.Number == text) {
                                messageListClicked(pMessageListModel->index(i, 0));
                                i = rows;
                            }
                        }

                        break;
                    } else {
                        QMessageBox::information(this,
                            "Warning", "Input Invalid",
                            QMessageBox::Ok, QMessageBox::Ok);
                    }
                } else {
                    QMessageBox::information(this,
                        "Warning", "Input were empty",
                        QMessageBox::Ok, QMessageBox::Ok);
                }
            } else
                break;
        }
    }

protected:
    void timerEvent(QTimerEvent* event);

private:
    QHBoxLayout* mainLayout;

    //左侧短信列表信息
    QVBoxLayout* messagesListLayout;
    QLabel* lastUpdate;
    QPushButton* createNewMessage;
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
