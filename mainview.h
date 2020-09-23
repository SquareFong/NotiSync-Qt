#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QStackedLayout>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include "mainviewphonedetails.h"
#include "mainviewphonenotifications.h"
#include "mainviewphonemessages.h"

//1号页面，主页面
namespace Ui {
class mainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(int, int, QWidget *parent = nullptr);
    ~MainView();

public slots:
    void listWidgetClicked(QListWidgetItem *item);
signals:
    void display(int number);

private:
    Ui::mainView *ui;
    QListWidget *listWidget;
    PhoneDetails *phoneDetails;
    PhoneNotifications *phoneNotifications;
    PhoneMessages *phoneMessages;
    QStackedLayout *stackLayout;
    QHBoxLayout *mainLayout;
};

#endif // MAINVIEW_H
