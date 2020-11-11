#include "loginview.h"
//#include "ui_loginview.h"

LoginView::LoginView(int width, int height, QWidget* parent)
    : QWidget(parent)
//, ui(new Ui::LoginView)
{
    //ui->setupUi(this);
    resize(width, height);
    //ui->label->setGeometry(width / 2 - 80, height / 2 - 30, 160, 40); //(x, y, width, height)
    //ui->pushButton->setGeometry(width / 2 - 80, height / 2 + 30, 160, 40);

    protocols = new QComboBox();
    protocols->addItem("http");
    protocols->addItem("https");

    address = new QLineEdit();

    port = new QLineEdit();

    uuid = new QLineEdit();

    login = new QPushButton("Login");

    configurations = new QGridLayout();
    configurations->addWidget(new QLabel("Protocols: "), 0, 0);
    configurations->addWidget(protocols, 0, 1);
    configurations->addWidget(new QLabel("Address: "), 1, 0);
    configurations->addWidget(address, 1, 1);
    configurations->addWidget(new QLabel("Protocols: "), 2, 0);
    configurations->addWidget(port, 2, 1);
    configurations->addWidget(new QLabel("Protocols: "), 3, 0);
    configurations->addWidget(uuid, 3, 1);
    configurations->addWidget(login, 4, 0, 1, 2);

    configurations->setColumnStretch(0, 1);
    configurations->setColumnStretch(1, 3);

    qrCode = new QLabel("hello");

    seperatrLine = new QFrame();
    seperatrLine->setFrameShape(QFrame::VLine);
    seperatrLine->setFrameShadow(QFrame::Plain);

    loginLayout = new QHBoxLayout();
    loginLayout->addWidget(qrCode);
    loginLayout->addWidget(seperatrLine);
    loginLayout->addLayout(configurations);
    loginLayout->setStretchFactor(qrCode, 1);
    loginLayout->setStretchFactor(configurations, 1);

    this->setLayout(loginLayout);
}

LoginView::~LoginView()
{
    //delete ui;
}
