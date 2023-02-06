#include "trayicon.h"
#include <QDebug>
TrayIcon::TrayIcon()
{

}
void TrayIcon::show(QString text, QString imagePath)
{
    // QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/com/kos/trays", "", "showTray");
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "showTrayIcon");

    QStringList menus{};
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    list.append(imagePath);
    list.append(text);
    list.append(menus);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);

}
void TrayIcon::setText(QString text){
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment",TRAY_PATH, "", "setText");
    QStringList menus{};
    QList<QVariant> list;
    list<<text;
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);
}
void TrayIcon::setImage(QString image){

    if(m_firstRun){
        show("",image);
        m_firstRun=false;
        return;
    }
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment",TRAY_PATH, "", "setImagePath");
    QStringList menus{};
    QList<QVariant> list;
    list.append(image);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);


}

void TrayIcon::updateIcon(QString imagePath)
{
    if(m_firstRun){
        show("",imagePath);
        m_firstRun=false;
        return;
    }

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "changeIcon");
    QStringList menus{};
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    list.append(imagePath);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);

}

void TrayIcon::setMax(long max)
{
    m_max = max;
}

void TrayIcon::setFirstRun(bool firstRun)
{
    lastImage = -1;
    m_firstRun = firstRun;
}

void TrayIcon::volumeChanged(qint32 volume)
{


    if(m_max == 0) return;




    int actualVolume = (volume*100)/m_max;

    if(actualVolume == 0 && lastImage !=0){
        // setImage("audio-volume-zero-panel");

        updateIcon("audio-volume-zero-panel");
        lastImage = 0;
    }
    else if(actualVolume < 25 && lastImage !=1){
        //updateIcon("audio-volume-low-panel");
        updateIcon("audio-volume-low-panel");


        lastImage = 1;
    }
    else if(actualVolume < 75 &&actualVolume > 25&& lastImage !=2){
        updateIcon("audio-volume-medium-panel");

        lastImage = 2;
    }
    else if(actualVolume > 75 && lastImage !=3){
        updateIcon("audio-volume-high-panel");

        lastImage = 3;
    }


    //setText(QString::number(volume));


}
