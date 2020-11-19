#include "src/widgets/widget.h"

#include <QApplication>
#include <thread>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    //    std::thread t1(&Widget::routine, &w);
    //    t1.detach();
    return a.exec();
}
