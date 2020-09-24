#include "mainviewphonedetails.h"
#include <QDebug>
#include <QSpacerItem>

PhoneDetails::PhoneDetails(QWidget *parent) :
    QWidget(parent)
{
    subTitle = new QLabel("Phone Details");
    QFont f("Noto Mono");
    f.setBold(true);
    f.setPointSize(16);
    subTitle->setFont(f);
    phoneAndroidVersion = new   QLabel(QString("OS:         "));
    phoneName = new             QLabel(QString("Model:      "));
    phoneKernelVersion = new    QLabel(QString("Kernel:     "));
    phoneUptime = new           QLabel(QString("Uptime:     "));
    phoneProcessor = new        QLabel(QString("Processor:  "));
    phoneResolution = new       QLabel(QString("Resolution: "));
    phoneRamUsage = new         QLabel(QString("Memory:     "));
    phoneStorageUsage = new     QLabel(QString("Storage:    "));

    mainLayout = new QGridLayout();
    mainLayout->columnStretch(1);

    mainLayout->addWidget(subTitle, 0, 0);
    mainLayout->addWidget(phoneAndroidVersion, 1, 0);mainLayout->addWidget(new QLabel(QString("Android 11")), 1, 1);
    mainLayout->addWidget(phoneName, 2, 0);mainLayout->addWidget(new QLabel(QString("Pixel 3a")), 2, 1);
    mainLayout->addWidget(phoneKernelVersion, 3, 0);mainLayout->addWidget(new QLabel(QString("4.9")), 3, 1);
    mainLayout->addWidget(phoneUptime, 4, 0);mainLayout->addWidget(new QLabel(QString("4 days, 1 hour")), 4, 1);
    mainLayout->addWidget(phoneProcessor, 5, 0);mainLayout->addWidget(new QLabel(QString("SDM670")), 5, 1);
    mainLayout->addWidget(phoneResolution, 6, 0);mainLayout->addWidget(new QLabel(QString("2220 x 1080")), 6, 1);
    mainLayout->addWidget(phoneRamUsage, 7, 0);mainLayout->addWidget(new QLabel(QString("2879 MiB / 3592 MiB")), 7, 1);
    mainLayout->addWidget(phoneStorageUsage, 8, 0);mainLayout->addWidget(new QLabel(QString("39.83GB / 64.00GB")), 8, 1);

    setLayout(mainLayout);
    qDebug() << geometry().x() << geometry().y() << width() << ' ' << height();
}

PhoneDetails::~PhoneDetails()
{
}
