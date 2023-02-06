#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QVariantMap>
#include <QtDBus/QtDBus>
#include "trayicon.h"

class BtDevice : public QObject
{
    Q_OBJECT
public:
    BtDevice(QObject *parent=nullptr);

    QString getObjectPath();
    void setObjectPath(QString objectPath);

    void setConnected(bool connected);
    void setDeviceName(QString deviceName);
    void setConnectedDeviceList(QStringList* list);

    void setTrusted();

    void removeDevice(QString path);



public slots:
    void PropertyChanged(QString interface_name, QVariantMap changed_properties,
                         QStringList invalidated_properties);
    void sendDBusSignal(QString signalName,QVariant var);


private:
    QString m_objectPath;
    QString m_deviceName="";
    bool m_connected=false;
    QStringList* connectedDevices;
    TrayIcon tray;



};

#endif // DEVICE_H
