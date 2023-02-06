#include "bluetoothdevice.h"

BluetoothDevice::BluetoothDevice()
{

}
void BluetoothDevice::disconnect(){
    QDBusInterface interface ("org.bluez", m_devicePath,"org.bluez.Device1", QDBusConnection::systemBus());
    interface.asyncCall("Disconnect");
}

void BluetoothDevice::makeConnection()
{
    QDBusInterface interface ("org.bluez", m_devicePath,"org.bluez.Device1", QDBusConnection::systemBus());
    interface.asyncCall("Connect");
}

void BluetoothDevice::removeDevice()
{
    QDBusInterface interface ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    QDBusObjectPath path;
    path.setPath(m_devicePath);
    interface.asyncCall("RemoveDevice",path);
}

const QString &BluetoothDevice::devicePath() const
{
    return m_devicePath;
}

void BluetoothDevice::setDevicePath(const QString &newDevicePath)
{
    m_devicePath = newDevicePath;
    emit devicePathChanged();
    getProperties();
    registerListener();

}

void BluetoothDevice::PropertyChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
{
    Q_UNUSED(invalidated_properties);
    Q_UNUSED(interface_name);

    //if(interface_name.compare("org.bluez.MediaPlayer1")==0){
    if(changed_properties.contains("Connected")){
        setConnected(changed_properties.value("Connected").toBool());
    }else if(changed_properties.contains("Paired")){
         setPaired(changed_properties.value("Paired").toBool());
    }
    //}
}

const QString &BluetoothDevice::adress() const
{
    return m_adress;
}

const QString &BluetoothDevice::icon() const
{
    return m_icon;
}

const QString &BluetoothDevice::name() const
{
    return m_name;
}

bool BluetoothDevice::trusted() const
{
    return m_trusted;
}

void BluetoothDevice::setPaired(bool paired)
{
    if(m_paired != paired){
        m_paired = paired;
        emit pairedChanged();
    }
}

bool BluetoothDevice::paired() const
{
    return m_paired;
}

void BluetoothDevice::setConnected(bool connected)
{
    if(m_connected != connected){
        m_connected = connected;
        emit connectedChanged();
    }
}

bool BluetoothDevice::connected() const
{
    return m_connected;
}

void BluetoothDevice::getProperties()
{
    QDBusInterface interface ("org.bluez", m_devicePath,"org.bluez.Device1", QDBusConnection::systemBus());
    m_connected = interface.property("Connected").toBool();
    m_name = interface.property("Name").toString();
    m_icon = interface.property("Icon").toString();
    setPaired(interface.property("Paired").toBool());
    emit connectedChanged();
    emit nameChanged();
    emit iconChanged();

}
void BluetoothDevice::registerListener()
{

    QDBusConnection::systemBus().connect("org.bluez",  m_devicePath,
                                         "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                                         SLOT(PropertyChanged(QString, QVariantMap, QStringList)));


}
