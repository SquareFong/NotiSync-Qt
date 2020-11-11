#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "src/core/configsmanager.h"
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
    explicit LoginView(int, int, QWidget* parent = nullptr);
    ~LoginView();

signals:
    void display(int number);

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
};

#endif // LOGINVIEW_H
