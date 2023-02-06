#include "trayicon.h"
#include <QtDBus/QtDBus>

TrayIcon::TrayIcon()
{

}
void TrayIcon::show(QString text, QString imagePath, int tray_id)
{
    //if(lastTray == tray_id && text.isEmpty()) return;

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

   // lastTray = tray_id;
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

int TrayIcon::getTrayid()
{
    return 33;
}

void TrayIcon::restTrayId()
{
    lastTray = 0;
}

void TrayIcon::updateIcon(QString imagePath){
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons", "", "changeIcon");
    QStringList menus{};
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    list.append(imagePath);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);
}
