#ifndef MAINVIEWPHONEDETAILS_H
#define MAINVIEWPHONEDETAILS_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class PhoneDetails : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneDetails(QWidget *parent = nullptr);
    ~PhoneDetails();

public slots:
    void selected(){
        emit display(0);
    }

signals:
    void display(int number);

private:
    QLabel *subTitle;
    QLabel *phoneName;
    QLabel *phoneProcessor;
    QLabel *phoneResolution;
    QLabel *phoneAndroidVersion;
    QLabel *phoneKernelVersion;
    QLabel *phoneUptime;
    QLabel *phoneRamUsage;
    QLabel *phoneStorageUsage;

    QGridLayout *mainLayout;
};

#endif // MAINVIEWPHONEDETAILS_H
