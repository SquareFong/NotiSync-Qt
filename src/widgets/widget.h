#ifndef WIDGET_H
#define WIDGET_H

#include "loginview.h"
#include "mainview.h"
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <unistd.h>

#include "src/core/notisyncclient.h"
//class LoginView;

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    void routine()
    {
        while (true) {
            nsc->fetchNotifications();
            nsc->fetchPhoneDetail();
            nsc->fetchMessages();
            sleep(1);
        }
    }

private:
    LoginView* loginView;
    MainView* mainView;
    //Ui::Widget *ui;
    QStackedLayout* stackLayout;
    QVBoxLayout* mainLayout;
    NotiSyncClient* nsc;
};
#endif // WIDGET_H
