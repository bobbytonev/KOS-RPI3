#include "trayicon.h"
#include <QDebug>
TrayIcon::TrayIcon()
{

}
//23101

//third digit from last
//2 - make button checked only in drop down
//1 - make button checked
//0 - make button unchecked

//second digit from last - text
//0 - show text on drop down and tray
//1 - show text only on tray
//2 - show text only on drop down


//last digit - image
//0 - show on drop down and tray
//1 - show only on tray
//2 - show only on drop down
//3 -
void TrayIcon::show(QStringList *connectionList)
{


   int size = connectionList->size();


   if(size == 0){
      int lastDigit = isPowered() ? 0:2;
       show("","bluetooth",(2320*10)+lastDigit);
       //close();
   }else if(size == 1){
       show(getName(connectionList->at(0)),"bluetooth",23200);
   }else{
       show(QString::number(size),"bluetooth",23200);
   }

}
void TrayIcon::close()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment", "/TrayIcons","","close");
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(23000);
    m.setArguments(list);

    QDBusConnection::systemBus().send(m);

}

bool TrayIcon::isPowered()
{
    QDBusInterface interface ("org.bluez", "/org/bluez/hci0",
                        "org.bluez.Adapter1", QDBusConnection::systemBus());


    return interface.property("Powered").toBool();
}

void TrayIcon::updateIcon(QString imagePath)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "changeIcon");
    QStringList menus{};
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    list.append(imagePath);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);

}

void TrayIcon::show(QString text, QString imagePath, int tray_id)
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "showTrayIcon");
    QStringList menus{};
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(tray_id);
    list.append(imagePath);
    list.append(text);
    list.append(menus);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);
}

QString TrayIcon::getName(QString objectPath)
{
    QDBusInterface interface ("org.bluez", objectPath,
                        "org.bluez.Device1", QDBusConnection::systemBus());


    return interface.property("Name").toString();

}



