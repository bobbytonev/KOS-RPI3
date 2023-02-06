#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDebug>
#include <unistd.h>


class TrayIcon : public QObject
{
    Q_OBJECT
public:
    TrayIcon();

    void setMap(QMap<QString, QStringList> *map);
    void show(QString text,QStringList menus);
    void close();

public slots:
    void sizeUpdated(int size);

private:
    const QString APP_NAME = "com.kos.usbtrayicon";
    const int TRAY_ID = 56100;
    const QString IMAGE_PATH = "usb-tray-icon";

    QMap<QString,QStringList>* m_map=NULL;


};

#endif // TRAYICON_H
