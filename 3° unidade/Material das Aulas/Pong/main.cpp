#include "mainpong.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPong w;
    w.show();

    return a.exec();
}
