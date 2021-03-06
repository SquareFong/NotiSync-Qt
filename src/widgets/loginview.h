#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "src/core/configsmanager.h"
#include "src/core/notisyncclient.h"
#include <QComboBox>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
/*这里是0号页面*/

class LoginView : public QWidget {
    Q_OBJECT

public:
    explicit LoginView(int, int, NotiSyncClient*, QWidget* parent = nullptr);
    ~LoginView();

signals:
    void display(int number);
public slots:
    void onLoginPushed();

private:
    //登录主页面
    QHBoxLayout* loginLayout;
    //TODO 左边部分
    QLabel* qrCode;

    QFrame* seperatrLine;

    //右边部分
    QGridLayout* configurations;

    QComboBox* protocols;
    QLineEdit* address;
    QLineEdit* port;
    QLineEdit* uuid;
    QPushButton* login;

    ConfigsManager* cfgMan;
    NotiSyncClient* const nsc;
};

#endif // LOGINVIEW_H
