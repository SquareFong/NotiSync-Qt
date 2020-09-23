#include "widget.h"
//#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //ui->setupUi(this);
    resize(800, 600);
    stackLayout = new QStackedLayout;

    loginView = new LoginView(800, 600);
    stackLayout->addWidget(loginView);
    connect(loginView, &LoginView::display, stackLayout, &QStackedLayout::setCurrentIndex);

    mainView = new MainView(800, 600);
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

