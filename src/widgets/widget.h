#ifndef WIDGET_H
#define WIDGET_H

#include "loginview.h"
#include "mainview.h"
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <unistd.h>

#include "src/core/notisyncclient.h"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    void routine()
    {
        while (true) {
            if (nsc->run()) {
                nsc->fetchNotifications();
                nsc->fetchPhoneDetail();
                nsc->fetchMessages();
            }
            sleep(1);
            printf("******fetch excuted******");
        }
    }

private:
    LoginView* loginView;
    MainView* mainView;
    QStackedLayout* stackLayout;
    QVBoxLayout* mainLayout;
    NotiSyncClient* nsc;
};
#endif // WIDGET_H
