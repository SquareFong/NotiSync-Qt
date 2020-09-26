#include "widget.h"
//#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //ui->setupUi(this);
    resize(900, 600);
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
}

Widget::~Widget()
{
    //delete ui;
}

