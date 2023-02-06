#include "wifiservice.h"

WifiService::WifiService(QString objectPath,QString state, QString name, int strenght)
{

    item.name =name;
    item.strenght = strenght;
    item.objectPath = objectPath;
    setState(state,true);



    QDBusConnection::systemBus().connect("net.connman",objectPath,
                                         "net.connman.Service", "PropertyChanged", this,
                                         SLOT(PropertyChanged(QString,QDBusVariant)));


}

WifiServiceItem WifiService::getItem()
{
    return item;
}

void WifiService::setState(QString state,bool firstRun)
{
    if(state == "online" || state == "ready") {
        showTray();
    }else if(state !="ready" && !firstRun){
        lastImage = -1;
        icon.show("","network-wireless",33202);
    }
    item.state =state;
}

void WifiService::setName(QString name)
{

}

void WifiService::setStrenght(int strenght)
{
    item.strenght = strenght;

    if(item.state == "online" || item.state == "ready"){
        showTray();
    }

}

void WifiService::showTray()
{
    int strenght=0;
    if(item.strenght < 25 && lastImage != 0 ){
        lastImage=0;
        strenght=25;
    }else if(item.strenght > 25 && item.strenght < 50 && lastImage !=1){
        lastImage = 1;
        strenght=50;
    }else if(item.strenght > 50 && item.strenght < 75 && lastImage !=2){
        lastImage = 2;
        strenght=75;
    }else if(item.strenght > 75 && lastImage !=3){
        lastImage = 3;
        strenght=100;

    }
    icon.show(item.name,"network-wireless-"+QString::number(strenght),33200);


}

void WifiService::PropertyChanged(QString name, QDBusVariant var)
{
    if(name.compare("State") == 0){
        QString state = var.variant().toString();
        setState(state,false);
    }else if(name.compare("Strength") == 0){
        int strenght =(int)var.variant().toUInt();
        setStrenght(strenght);
    }
}
