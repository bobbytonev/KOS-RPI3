#include <QCoreApplication>
#include "wifimanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    wifimanager manager;


    return a.exec();
}
