#include <QCoreApplication>
#include "bluetoothmanager.h"
#include "trayicon.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BluetoothManager bm(&a);

/*
    TrayIcon icon;

    int number = atoi(argv[1]);


    if(number == 1){
        icon.show("","go-home",3300*10+number);
    }else{
        icon.show("","go-home",3300*10+number);
    }
    */
    // icon.show("","settings-Wi-Fi",number);

    //icon.show("","go-home",44002);
    //icon.show("","go-home",63002);
    //icon.show("","settings-Wi-Fi",73002);

    //icon.show("","bluetooth",48002);




    return a.exec();
}
