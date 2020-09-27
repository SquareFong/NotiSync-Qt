#ifndef PHONEMESSAGESCHAT_H
#define PHONEMESSAGESCHAT_H

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QStandardItemModel>

class PhoneMessagesChat : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneMessagesChat(QWidget *parent = nullptr);

signals:

private:
    QStackedLayout *stacklayout;

    QVBoxLayout *singleChatView;
    QHBoxLayout *singleChatViewTitle;
    QListView *singleChatContent;
};

#endif // PHONEMESSAGESCHAT_H
