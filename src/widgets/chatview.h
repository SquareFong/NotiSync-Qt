#ifndef CHATVIEW_H
#define CHATVIEW_H

#include "messageitemwidget.h"
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
    explicit ChatView(QWidget* parent = nullptr);
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
    }
    inline void scrollToButtom()
    {
        chatContent->scrollToBottom();
    }

    QLabel* contactName;

private:
    QVBoxLayout* mainLayout;
    QPushButton* deleteChat;
    QListWidget* chatContent;
    QTextEdit* inputArea;
};

#endif // CHATVIEW_H
