#include "loginview.h"
#include "ui_loginview.h"

LoginView::LoginView(int width, int height, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
    resize(width, height);
    ui->label->setGeometry(width/2-80, height/2-30, 160, 40); //(x, y, width, height)
    ui->pushButton->setGeometry(width/2-80, height/2+30, 160, 40);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_pushButton_clicked()
{
    emit display(1);
}
