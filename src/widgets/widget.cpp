#include "widget.h"
#include <thread>
using namespace std;

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    resize(1100, 600);
    stackLayout = new QStackedLayout;

    loginView = new LoginView(width(), height());
    stackLayout->addWidget(loginView);
    connect(loginView, &LoginView::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainView = new MainView(width(), height());
    stackLayout->addWidget(mainView);
    connect(mainView, &MainView::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);

    nsc = new NotiSyncClient();
    nsc->setUUID("7517e18a-40a6-4902-a7c9-23bd0ef7f00f");
    nsc->setServer("http", "127.0.0.1", "9000");

    //    std::thread t1(&Widget::routine, this);
    //    t1.join();
}

Widget::~Widget()
{
    //delete ui;
}
