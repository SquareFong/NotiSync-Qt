#include "loginview.h"

LoginView::LoginView(int width, int height, NotiSyncClient* NotiSyncClient, QWidget* parent)
    : QWidget(parent)
    , nsc(NotiSyncClient)
{
    resize(width, height);

    map<string, string> serverCfg;
    cfgMan = new ConfigsManager();
    try {
        if (cfgMan->readServerConfig()) {
            serverCfg = cfgMan->getServerconfig();
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

    protocols->setCurrentText(serverCfg.find("protocol")->second.c_str());

    address = new QLineEdit();
    address->setText(serverCfg.find("address")->second.c_str());

    port = new QLineEdit();
    port->setText(serverCfg.find("port")->second.c_str());
    port->setValidator(new QIntValidator(0, 65536));

    uuid = new QLineEdit();
    uuid->setText(serverCfg.find("uuid")->second.c_str());
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
    string prot = protocols->currentText().toStdString();
    string addr = address->text().toStdString();
    string port = this->port->text().toStdString();
    string uuid = this->uuid->text().toStdString();

    nsc->setServer(prot, addr, port);
    nsc->setUUID(uuid);

    //TODO 给nsc加登录验证，登录成功再保存
    //nsc->setRunable(true);
    map<string, string>& configs = cfgMan->getServerconfig();
    set<string> properties = { "protocol", "address", "port", "uuid", "isRun" };
    for (auto& it : properties) {
        auto item = configs.find(it);
        if (item != configs.end()) {
            if (it == "protocol") {
                item->second = prot;
            } else if (it == "address") {
                item->second = addr;
            } else if (it == "port") {
                item->second = port;
            } else if (it == "uuid") {
                item->second = uuid;
            } else if (it == "isRun") {
                item->second = "true";
            } else {
            }
        } else {
            if (it == "protocol") {
                configs.insert(pair<string, string>(it, prot));
            } else if (it == "address") {
                configs.insert(pair<string, string>(it, addr));
            } else if (it == "port") {
                configs.insert(pair<string, string>(it, port));
            } else if (it == "uuid") {
                configs.insert(pair<string, string>(it, uuid));
            } else if (it == "isRun") {
                configs.insert(pair<string, string>(it, "true"));
            } else {
            }
        }
    }
    cfgMan->saveServerConfig();
    emit display(1);
}

LoginView::~LoginView()
{
}
