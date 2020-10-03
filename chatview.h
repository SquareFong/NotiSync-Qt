#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QDebug>
#include "messageitemwidget.h"

class ChatView : public QWidget
{
    Q_OBJECT
public:
    explicit ChatView(QWidget *parent = nullptr);
    void pushContent(MessageItemData data);
    void resizeEvent(QResizeEvent *event){
        //chatContent->resize(width(),height());
        qDebug()  << "ChatView:" << width() << height();
        for(int i = 0; i < chatContent->count(); ++i){
            QListWidgetItem *item = chatContent->item(i);
            MessageItemWidget *w = (MessageItemWidget*)chatContent->itemWidget(item);
            w->setFixedWidth(this->width());
            w->resizeEvent(nullptr);
            item->setSizeHint(w->sizeWidget);
            //chatContent->setItemWidget(item, w);
        }
    }
signals:

private:
    QVBoxLayout *mainLayout;
    QLabel *contactName;
    QPushButton *deleteChat;
    QListWidget *chatContent;
    QTextEdit *inputArea;
};

#endif // CHATVIEW_H
