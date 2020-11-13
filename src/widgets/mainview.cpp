#include "mainview.h"

#include <QMouseEvent>

class myQListWidgetItem : public QListWidgetItem {
signals:
    void selected(int number)
    {
        printf("Selected: %d \n", number);
    }

public:
    int index;
    void setIndex(int number)
    {
        index = number;
    }
};

void MainView::listWidgetClicked(QListWidgetItem* item)
{
    myQListWidgetItem* m = (myQListWidgetItem*)item;
    stackLayout->setCurrentIndex(m->index);
}

MainView::MainView(int width, int height, QWidget* parent)
    : QWidget(parent)
{
    resize(width, height);

    //左侧列表初始化
    listWidget = new QListWidget(this);
    listWidget->setSelectionMode(QListWidget::SingleSelection);
    connect(listWidget, &QListWidget::itemClicked, this, &MainView::listWidgetClicked);
    // 详情
    myQListWidgetItem* phoneDetailButton = new myQListWidgetItem();
    phoneDetailButton->setText("Detail");
    phoneDetailButton->setIcon(QIcon(":/Icons/smartphone"));
    phoneDetailButton->setTextAlignment(Qt::AlignLeft);
    phoneDetailButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    phoneDetailButton->setIndex(0);
    listWidget->addItem(phoneDetailButton);
    // 通知
    myQListWidgetItem* notiButton = new myQListWidgetItem();
    notiButton->setText("Notifications");
    notiButton->setIcon(QIcon(":/Icons/notification"));
    notiButton->setTextAlignment(Qt::AlignLeft);
    notiButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    notiButton->setIndex(1);
    listWidget->addItem(notiButton);
    // 短信
    myQListWidgetItem* smsButton = new myQListWidgetItem();
    smsButton->setText("Messages");
    smsButton->setIcon(QIcon(":/Icons/messages"));
    smsButton->setTextAlignment(Qt::AlignLeft);
    smsButton->setIndex(2);
    listWidget->addItem(smsButton);

    listWidget->setCurrentRow(0);

    //主界面右边部分
    stackLayout = new QStackedLayout();

    phoneDetails = new PhoneDetails(this);
    stackLayout->addWidget(phoneDetails);

    phoneNotifications = new PhoneNotifications();
    stackLayout->addWidget(phoneNotifications);

    phoneMessages = new PhoneMessages();
    stackLayout->addWidget(phoneMessages);

    //设置主页面
    mainLayout = new QHBoxLayout();

    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(stackLayout);

    mainLayout->setStretchFactor(listWidget, 1);
    mainLayout->setStretchFactor(stackLayout, 4);
    setLayout(mainLayout);
}

MainView::~MainView()
{
}
