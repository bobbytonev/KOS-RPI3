#include <QCoreApplication>
#include "clock.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Clock clock;
    return a.exec();

}
