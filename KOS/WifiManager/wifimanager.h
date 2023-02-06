#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <QObject>
#include "wifiservice.h"
#include "trayicon.h"

struct ServiceArray{
    QDBusObjectPath path;
    QVariantMap map;
};

class wifimanager : public QObject
{
    Q_OBJECT
    typedef QMap<QDBusObjectPath,QVariantMap> passedMapType;
public:
    wifimanager();
    ~wifimanager();
    void setPowered(bool powered);



    void removeService(QString path);
    void addService(QString path ,QVariantMap map);
    void getTechnologies();
    void registerDbus();

    bool setServiceArray(QList<ServiceArray>& list,const QDBusMessage& message);


public slots:
    void ServicesChanged(QList<QVariant> vlist,QList<QDBusObjectPath> servicesRemoved,QDBusMessage message);
    void techPropertyChanged(QString name,QDBusVariant var);
    void getServices();
    void clicked();
    void longPress();
    void init();
    Q_SCRIPTABLE bool powered();

private:
    bool m_powered;
    QDBusInterface *wifi = NULL;
    QMap<QString,WifiService*> services;
    TrayIcon icon;

    const QString DBUS_NAME ="net.connman";
    const QString DBUS_INTERFACE = "net.connman.Manager";
};



#endif // WIFIMANAGER_H
