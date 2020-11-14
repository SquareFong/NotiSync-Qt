#ifndef MAINVIEWPHONEDETAILS_H
#define MAINVIEWPHONEDETAILS_H

#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <map>

#include "src/core/notisyncclient.h"

/*详情页（mainView）的0号页面*/
class PhoneDetails : public QWidget {
    Q_OBJECT

public:
    explicit PhoneDetails(NotiSyncClient* NotiSyncClient, QWidget* parent = nullptr);
    ~PhoneDetails();

protected:
    void timerEvent(QTimerEvent* event);

private:
    QLabel* subTitle;
    QLabel* phoneName;
    QLabel* phoneProcessor;
    QLabel* phoneResolution;
    QLabel* phoneAndroidVersion;
    QLabel* phoneKernelVersion;
    QLabel* phoneUptime;
    QLabel* phoneRamUsage;
    QLabel* phoneStorageUsage;
    QGridLayout* mainLayout;
    NotiSyncClient* const nsc;
    map<string, string> details;

    int m_timerid;
};

#endif // MAINVIEWPHONEDETAILS_H
