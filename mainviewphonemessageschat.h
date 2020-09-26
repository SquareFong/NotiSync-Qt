#ifndef PHONEMESSAGESCHAT_H
#define PHONEMESSAGESCHAT_H

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
class PhoneMessagesChat : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneMessagesChat(QWidget *parent = nullptr);

signals:

private:
    QStackedLayout *stacklayout;
};

#endif // PHONEMESSAGESCHAT_H
