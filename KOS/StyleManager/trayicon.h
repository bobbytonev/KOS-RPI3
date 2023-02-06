#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>


class TrayIcon : public QObject
{
    Q_OBJECT
public:
    TrayIcon();

    void show(QString text,QString imagePath);
    void close();

private:
    const QString APP_NAME = "com.kos.stylemanager";
    const int TRAY_ID = 46000;
    //const QString IMAGE_PATH = "weather";


};

#endif // TRAYICON_H
