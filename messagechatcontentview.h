#ifndef MESSAGECHATCONTENTVIEW_H
#define MESSAGECHATCONTENTVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>

class MessageChatContentView : public QWidget
{
    Q_OBJECT
public:
    explicit MessageChatContentView(QWidget *parent = nullptr);

signals:

private:
    QVBoxLayout * chatView;

    QHBoxLayout *title;
    QLabel *contact;
    QPushButton *deleteChat;

    QListView *chatContent;
};

#endif // MESSAGECHATCONTENTVIEW_H
