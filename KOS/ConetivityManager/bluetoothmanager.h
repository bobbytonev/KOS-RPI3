#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include <QDebug>
#include "device.h"
#include "trayicon.h"

class BluetoothManager:public QObject
{
    Q_OBJECT

public:
    BluetoothManager(QObject* parent=nullptr);
    ~BluetoothManager();
    void setDiscoverable();
    void findConnection();
    void init();
    void scan();
    void exposeDBusApi();


public slots:
    void InterfacesRemoved(QDBusObjectPath path,QStringList list);
    void InterfacesAdded(QDBusObjectPath path,QVariantMap list);
    void clicked();
    void showTray();
    void stateChanged(QString interface_name, QVariantMap changed_properties,
                      QStringList invalidated_properties);
    void longPress();

    Q_SCRIPTABLE int size();
    Q_SCRIPTABLE QString get(int index);
    Q_SCRIPTABLE void setPower(bool power);
    Q_SCRIPTABLE void setAlias(QString alias);

private:
    bool m_power;
    //QString m_objectPath="";

    QStringList connectedDevice;

    QMap<QString,BtDevice*> allDevice;
    TrayIcon icon;
    QDBusConnection session = QDBusConnection::sessionBus();



};

#endif // BLUETOOTHMANAGER_H
