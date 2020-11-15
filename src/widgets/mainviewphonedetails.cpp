#include "mainviewphonedetails.h"
#include <QDebug>
#include <QSpacerItem>
#include <QTimerEvent>

int t = 0;
void PhoneDetails::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerid) {
        printf("Debug: Hit: PhoneDetails::timerEvent %d\n", ++t);
        PhoneDetail pd = nsc->getPhoneDetail();

        phoneAndroidVersion->setText(pd.osVersion.c_str());
        phoneName->setText(pd.model.c_str());
        phoneKernelVersion->setText(pd.kernel.c_str());
        phoneUptime->setText(pd.uptime.c_str());
        phoneProcessor->setText(pd.processor.c_str());
        phoneRamUsage->setText(pd.memoryUsage.c_str());
        phoneStorageUsage->setText(pd.storageUsage.c_str());
    }
}

PhoneDetails::PhoneDetails(NotiSyncClient* NotiSyncClient, QWidget* parent)
    : QWidget(parent)
    , nsc(NotiSyncClient)
    , m_timerid(startTimer(300))
{
    subTitle = new QLabel("Phone Details");
    QFont f("Noto Mono");
    f.setBold(true);
    f.setPointSize(16);
    subTitle->setFont(f);
    phoneAndroidVersion = new QLabel(QString("OS:         "));
    phoneName = new QLabel(QString("Model:      "));
    phoneKernelVersion = new QLabel(QString("Kernel:     "));
    phoneUptime = new QLabel(QString("Uptime:     "));
    phoneProcessor = new QLabel(QString("Processor:  "));
    //    phoneResolution = new QLabel(QString("Resolution: "));
    phoneRamUsage = new QLabel(QString("Memory:     "));
    phoneStorageUsage = new QLabel(QString("Storage:    "));

    mainLayout = new QGridLayout();
    mainLayout->columnStretch(1);

    details.insert(pair<string, string>("OsVersion", "Unknown"));
    details.insert(pair<string, string>("Model", "Unknown"));
    details.insert(pair<string, string>("Kernel", "Unknown"));
    details.insert(pair<string, string>("Uptime", "Unknown"));
    details.insert(pair<string, string>("Processor", "Unknown"));
    details.insert(pair<string, string>("MemoryUsage", "Unknown"));
    details.insert(pair<string, string>("StorageUsage", "Unknown"));

    mainLayout->addWidget(subTitle, 0, 0);

    mainLayout->addWidget(new QLabel(QString("OS:        ")), 1, 0);
    phoneAndroidVersion->setText(details.find("OsVersion")->second.c_str());
    mainLayout->addWidget(phoneAndroidVersion, 1, 1);

    mainLayout->addWidget(new QLabel(QString("Model:     ")), 2, 0);
    phoneName->setText(details.find("Model")->second.c_str());
    mainLayout->addWidget(phoneName, 2, 1);

    mainLayout->addWidget(new QLabel(QString("Kernel:    ")), 3, 0);
    phoneKernelVersion->setText(details.find("Kernel")->second.c_str());
    mainLayout->addWidget(phoneKernelVersion, 3, 1);

    mainLayout->addWidget(new QLabel(QString("Uptime:    ")), 4, 0);
    phoneUptime->setText(details.find("Uptime")->second.c_str());
    mainLayout->addWidget(phoneUptime, 4, 1);

    mainLayout->addWidget(new QLabel(QString("Processor: ")), 5, 0);
    phoneProcessor->setText(details.find("Processor")->second.c_str());
    mainLayout->addWidget(phoneProcessor, 5, 1);

    //    mainLayout->addWidget(new QLabel(QString("Resolution: ")), 6, 0);
    //    phoneResolution->setText(details.find("Resolution")->second.c_str());
    //    mainLayout->addWidget(phoneResolution, 6, 1);

    mainLayout->addWidget(new QLabel(QString("Memory:    ")), 7, 0);
    phoneRamUsage->setText(details.find("MemoryUsage")->second.c_str());
    mainLayout->addWidget(phoneRamUsage, 7, 1);

    mainLayout->addWidget(new QLabel(QString("Storage:   ")), 8, 0);
    phoneStorageUsage->setText(details.find("StorageUsage")->second.c_str());
    mainLayout->addWidget(phoneStorageUsage, 8, 1);

    mainLayout->setColumnStretch(0, 5);
    mainLayout->setColumnStretch(1, 24);

    setLayout(mainLayout);
    qDebug() << geometry().x() << geometry().y() << width() << ' ' << height();
}

PhoneDetails::~PhoneDetails()
{
}
