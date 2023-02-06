#include "trayicon.h"

TrayIcon::TrayIcon()
{



}

void TrayIcon::setMap(QMap<QString,QStringList> *map)
{
    if(m_map == NULL){

        m_map = map;
    }
}

void TrayIcon::show(QString text,QStringList menus)
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "showTrayIcon");
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    list.append(IMAGE_PATH);
    list.append(text);
    list.append(menus);
    m.setArguments(list);


    QDBusConnection::systemBus().send(m);



}

void TrayIcon::close()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment", "/TrayIcons","","close");
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    m.setArguments(list);

    QDBusConnection::systemBus().send(m);

}

void TrayIcon::sizeUpdated(int size)
{


    switch(size){
    case 0:
        close();
        break;
    case 1:{
        QStringList menus{tr("Open"),tr("Eject")};
        show("",menus);
    }
        break;
    default:
    {
        QStringList menus;
        if(m_map == NULL) break;
        for(int i=0;i<size;i++){
            menus.append(m_map->values().at(i).at(1));
        }
        show(QString::number(size),menus);
    }
        break;
    }
}

