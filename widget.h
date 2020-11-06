#ifndef WIDGET_H
#define WIDGET_H

#include "loginview.h"
#include "mainview.h"
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QWidget>

//class LoginView;

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    LoginView* loginView;
    MainView* mainView;
    //Ui::Widget *ui;
    QStackedLayout* stackLayout;
    QVBoxLayout* mainLayout;
};
#endif // WIDGET_H
