#include "loginview.h"

LoginView::LoginView(int width, int height, QWidget* parent)
    : QWidget(parent)
{
    resize(width, height);

    ServerConfig serverCfg;
    try {
        ConfigsManager cfgMan;
        if (cfgMan.readServerConfig()) {
            serverCfg = cfgMan.getServerconfig();
            //TODO 检查配置合法性
        } else {
            //TODO 给初始化操作并写入本地文件
        }
    } catch (const char* e) {
        printf("Exception: %s\n", e);
        assert(0);
    }
    protocols = new QComboBox();
    protocols->addItem("");
    protocols->addItem("http");
    protocols->addItem("https");

    protocols->setCurrentText(serverCfg.protocol.c_str());

    address = new QLineEdit();
    address->setText(serverCfg.address.c_str());

    port = new QLineEdit();
    port->setText(serverCfg.port.c_str());
    port->setValidator(new QIntValidator(0, 65536));

    uuid = new QLineEdit();
    uuid->setText(serverCfg.uuid.c_str());
    uuid->setValidator(
        new QRegExpValidator(
            QRegExp("[0-9a-f]{8}(-[0-9a-f]{4}){3}-[0-9a-f]{12}")));

    login = new QPushButton("Login");
    connect(login, &QPushButton::clicked, this, &LoginView::onLoginPushed);

    configurations = new QGridLayout();
    configurations->addWidget(new QLabel("Protocols: "), 0, 0);
    configurations->addWidget(protocols, 0, 1);
    configurations->addWidget(new QLabel("Address: "), 1, 0);
    configurations->addWidget(address, 1, 1);
    configurations->addWidget(new QLabel("Port: "), 2, 0);
    configurations->addWidget(port, 2, 1);
    configurations->addWidget(new QLabel("UUID: "), 3, 0);
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

void LoginView::onLoginPushed()
{
    //TODO 保存配置文件，设置来自Widget.cpp的nsc;
    emit display(1);
}

LoginView::~LoginView()
{
}
