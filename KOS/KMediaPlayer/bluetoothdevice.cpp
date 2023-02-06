#include "bluetoothdevice.h"

BluetoothDevice::BluetoothDevice()
{

}

void BluetoothDevice::setStatus(QString status)
{
    m_status = status;
    emit statusChanged();
}

QString BluetoothDevice::status()
{
    return m_status;
}

void BluetoothDevice::setTitle(QString title)
{
    m_title = title;
    emit titleChanged();
}

QString BluetoothDevice::title()
{
    return m_title;
}

void BluetoothDevice::setDevicePath(QString objectPath)
{

    m_objectPath = objectPath;
    setProperties();
    registerListener();
}

QString BluetoothDevice::devicePath()
{
    return m_objectPath;
}

void BluetoothDevice::setProperties()
{
    QDBusInterface interface ("org.bluez", m_objectPath+"/player0","org.bluez.MediaPlayer1", QDBusConnection::systemBus());
    m_status = interface.property("Status").toString();
    QDBusInterface iface("org.bluez",
                         m_objectPath+"/player0",
                         "org.freedesktop.DBus.Properties",
                         QDBusConnection::systemBus());

    QDBusMessage reply = iface.call("Get", "org.bluez.MediaPlayer1", "Track");
    QDBusVariant dbvFirst = reply.arguments().first().value<QDBusVariant>();
    QVariant v = dbvFirst.variant();
    m_title =getTitle(v);




}

void BluetoothDevice::registerListener()
{

    QDBusConnection::systemBus().connect("org.bluez",  m_objectPath+"/player0",
                                         "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                                         SLOT(PropertyChanged(QString, QVariantMap, QStringList)));


}

QString BluetoothDevice::getTitle(QVariant var)
{

    const QDBusArgument &arg= var.value<QDBusArgument>();


    QMap<QString,QVariant> map;


    arg.beginMap();
    while(!arg.atEnd()) {
        arg.beginMapEntry();
        QString k;
        QVariant v;
        arg>>k;
        arg>>v;
        map.insert(k,v);

        arg.endMapEntry();
    }
    arg.endMap();
    return map.value("Title").toString();
}
void BluetoothDevice::PropertyChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
{
    Q_UNUSED(invalidated_properties);
    Q_UNUSED(interface_name);
    //if(interface_name.compare("org.bluez.MediaPlayer1")==0){
    if(changed_properties.contains("Status")){
        setStatus(changed_properties.value("Status").toString());

    }else if(changed_properties.contains("Track")){
        QVariant v = changed_properties.value("Track");
        setTitle(getTitle(v));


    }
    //}
}
