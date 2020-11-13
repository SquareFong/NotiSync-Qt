#include "widget.h"
#include <thread>
using namespace std;

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    resize(1100, 600);
    stackLayout = new QStackedLayout;
    nsc = new NotiSyncClient();

    loginView = new LoginView(width(), height(), nsc);
    stackLayout->addWidget(loginView);
    connect(loginView, &LoginView::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainView = new MainView(width(), height(), nsc);
    stackLayout->addWidget(mainView);
    connect(mainView, &MainView::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
}

Widget::~Widget()
{
    //delete ui;
}
