#include "bluetoothmanager.h"

BluetoothManager::BluetoothManager()
{

    init();
}

bool BluetoothManager::powered()
{
    return m_powered;
}

void BluetoothManager::setPowered(bool powered)
{
    if(m_powered !=powered){
        m_powered = powered;

        emit poweredChanged();


    }
}

QString BluetoothManager::name()
{
    return m_name;
}

void BluetoothManager::setName(QString name)
{
    if(m_name !=name){
        m_name = name;
        emit nameChanged();
    }
}

bool BluetoothManager::enabled()
{
    return m_enabled;
}

void BluetoothManager::setEnabled(bool enabled)
{
    if(m_enabled !=enabled) {
        m_enabled = enabled;
        emit enabledChanged();
    }
}



void BluetoothManager::init()
{
    QDBusInterface adapter ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    //adapter->setParent(this);

    m_powered=adapter.property("Powered").toBool();
    m_name=adapter.property("Alias").toString();

    QDBusConnection::systemBus().connect("org.bluez",  "/org/bluez/hci0",
                                         "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                                         SLOT(PropertyChanged(QString, QVariantMap, QStringList)));
}

void BluetoothManager::setProperty(QString method, QVariant var, bool errorSlot)
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.btmanager","/ConnectedDevices","",method);
    QList<QVariant> args;
    args<<var;
    m.setArguments(args);
    if(errorSlot){
        setEnabled(false);
        QDBusConnection::sessionBus().callWithCallback(m,this,SLOT(returnMethod()),SLOT(error()));
    }
    if(!errorSlot)
        QDBusConnection::sessionBus().asyncCall(m);


}
void BluetoothManager::PropertyChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
{

    Q_UNUSED(interface_name);
    Q_UNUSED(invalidated_properties);

    if(changed_properties.contains("Powered")){
        bool powered = changed_properties.value("Powered").toBool();
        setPowered(powered);
    }else if(changed_properties.contains("Alias")){
        setName(changed_properties.value("Alias").toString());
    }
}

void BluetoothManager::error()
{
    setEnabled(false);
    m_powered = !m_powered;
}

void BluetoothManager::returnMethod()
{
    setEnabled(true);
}




