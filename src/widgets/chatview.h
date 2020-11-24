#ifndef CHATVIEW_H
#define CHATVIEW_H

#include "messageitemwidget.h"
#include "src/core/notisyncclient.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class ChatView : public QWidget {
    Q_OBJECT
public:
    explicit ChatView(NotiSyncClient* NotiSyncClient, QWidget* parent = nullptr);
    void pushContent(MessageItemData data);
    void resizeEvent(QResizeEvent* event)
    {
        //chatContent->resize(width(),height());
        qDebug() << "ChatView:" << width() << height();
        for (int i = 0; i < chatContent->count(); ++i) {
            QListWidgetItem* item = chatContent->item(i);
            MessageItemWidget* w = (MessageItemWidget*)chatContent->itemWidget(item);
            w->setFixedWidth(this->width());
            w->resizeEvent(nullptr);
            item->setSizeHint(w->sizeWidget);
            //chatContent->setItemWidget(item, w);
        }
    }
    void clear()
    {
        chatContent->clear();
        inputArea->clear();
    }
    inline void scrollToButtom()
    {
        chatContent->scrollToBottom();
    }

    void setContact(const QString contact)
    {
        contactName->setText(contact);
        currentContactNumber = contact;
        inputArea->setFocus();
    }

private slots:
    void sendMessageClicked()
    {
        Message m;
        m.number = currentContactNumber.toStdString();
        m.body = inputArea->toPlainText().toStdString();
        time_t t;
        time(&t);
        m.date = to_string(t * 1000);
        m.type = 2;

        MessageItemData item { 1, m.body.c_str(), stol(m.date) };
        pushContent(item);

        nsc->sendNewMessage(m);
        inputArea->clear();
    }

private:
    QLabel* contactName;
    QVBoxLayout* mainLayout;
    QPushButton* deleteChat;
    QListWidget* chatContent;
    QTextEdit* inputArea;
    QPushButton* sendMessage;
    QString currentContactNumber; //用来保存当前联系人号码
    NotiSyncClient* const nsc;
};

#endif // CHATVIEW_H
