#ifndef MAINVIEWPHONEMESSAGES_H
#define MAINVIEWPHONEMESSAGES_H

#include <QWidget>

namespace Ui {
class PhoneMessages;
}

class PhoneMessages : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneMessages(QWidget *parent = nullptr);
    ~PhoneMessages();

private:
};

#endif // MAINVIEWPHONEMESSAGES_H
