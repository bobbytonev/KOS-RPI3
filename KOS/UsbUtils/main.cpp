#include <QCoreApplication>
#include <QGuiApplication>
//#include "usbdbus.h"
#include "usbutils.h"


int main(int argc, char *argv[])
{
    //formula
    //11 - number of butes per sector //2 bytes
    //13 - number of sectors per cluster //1 bytes
    //14 - reserved sectors //2 bytes
    //16 - number of FATs //1 byte
    //36 - number of sectors per FAT


    QCoreApplication::setSetuidAllowed(true);
    QCoreApplication a(argc, argv);

    usbutils usb;


    return a.exec();

}
