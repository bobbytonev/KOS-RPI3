#include <QCoreApplication>
#include "volume.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QThread thread;
    Volume volume;
    //volume.moveToThread(&thread);
    //thread.start();









    return a.exec();
}
