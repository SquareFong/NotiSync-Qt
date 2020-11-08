#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "mainviewphonedetails.h"
#include "mainviewphonemessages.h"
#include "mainviewphonenotifications.h"
#include <QGridLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedLayout>
#include <QWidget>

/*1号页面，主页面*/
namespace Ui {
class mainView;
}

class MainView : public QWidget {
    Q_OBJECT

public:
    explicit MainView(int, int, QWidget* parent = nullptr);
    ~MainView();

public slots:
    void listWidgetClicked(QListWidgetItem* item);
signals:
    void display(int number);

private:
    Ui::mainView* ui;
    QListWidget* listWidget;
    PhoneDetails* phoneDetails;
    PhoneNotifications* phoneNotifications;
    PhoneMessages* phoneMessages;
    QStackedLayout* stackLayout;
    QHBoxLayout* mainLayout;
};

#endif // MAINVIEW_H
