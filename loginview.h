#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

//这里是0号页面

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(int, int, QWidget *parent = nullptr);
    ~LoginView();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
