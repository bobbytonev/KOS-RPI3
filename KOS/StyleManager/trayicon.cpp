#include "trayicon.h"
#include <QDebug>
TrayIcon::TrayIcon()
{

}

void TrayIcon::show(QString text, QString imagePath)
{
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

void TrayIcon::close()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment", "/TrayIcons","","close");
    QList<QVariant> list;
    list.append(APP_NAME);
    list.append(TRAY_ID);
    m.setArguments(list);
    QDBusConnection::systemBus().send(m);
}
