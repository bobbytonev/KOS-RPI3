#include "device.h"

BtDevice::BtDevice(QObject *parent) : QObject(parent)
{


}





QString BtDevice::getObjectPath()
{
    return m_objectPath;
}

void BtDevice::setObjectPath(QString objectPath)
{

    m_objectPath = objectPath;
    QDBusConnection::systemBus().connect("org.bluez",  m_objectPath,
                                         "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                                         SLOT(PropertyChanged(QString, QVariantMap, QStringList)));


}

void BtDevice::setConnected(bool connected)
{
    if(m_connected==connected) return;

    if(connected){
        if(connectedDevices->contains(m_objectPath)) return;
        connectedDevices->append(m_objectPath);
        sendDBusSignal("deviceAdded",m_objectPath);

    }else{
        removeDevice(m_objectPath);

    }
    tray.show(connectedDevices);
    m_connected = connected;
}

void BtDevice::setDeviceName(QString deviceName)
{
    m_deviceName = deviceName;
}

void BtDevice::setConnectedDeviceList(QStringList *list)
{
    connectedDevices = list;
}

void BtDevice::setTrusted()
{
    QDBusInterface interface ("org.bluez", m_objectPath,
                              "org.bluez.Device1", QDBusConnection::systemBus());
    interface.setProperty("Trusted",true);

}

void BtDevice::removeDevice(QString path)
{
    for(int i=0;i<connectedDevices->size();i++){
        if(connectedDevices->at(i).compare(path)==0){
            sendDBusSignal("deviceRemoved",i);


            connectedDevices->removeAt(i);
            break;
        }
    }


}

void BtDevice::PropertyChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
{
    Q_UNUSED(invalidated_properties);
    if(interface_name.compare("org.bluez.Device1")==0){
        if(changed_properties.contains("Connected")){

            bool connected = changed_properties.value("Connected").toBool();
            setConnected(connected);
        }
    }
}

void BtDevice::sendDBusSignal(QString signalName,QVariant var)
{
    QDBusMessage m =QDBusMessage::createSignal("/ConnectedDevices","com.kos.btmanager", signalName);
    QList<QVariant> list;
    list.append(var);
    m.setArguments(list);
    QDBusConnection::sessionBus().send(m);
}
