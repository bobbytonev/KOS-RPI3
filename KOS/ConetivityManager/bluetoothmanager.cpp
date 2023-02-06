#include "bluetoothmanager.h"

BluetoothManager::BluetoothManager(QObject *parent) : QObject(parent)
{
    setDiscoverable();
    findConnection();
    init();
    exposeDBusApi();
}

BluetoothManager::~BluetoothManager()
{

    qDeleteAll(allDevice);
}

void BluetoothManager::setDiscoverable()
{
    QDBusInterface nm2 ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    nm2.setProperty("PairableTimeout",0);
    nm2.setProperty("DiscoverableTimeout",0);
    nm2.setProperty("Discoverable",true);
    nm2.setProperty("Pairable",true);
}

void BluetoothManager::findConnection()
{

    QDBusMessage m = QDBusMessage::createMethodCall("org.bluez",
                                                    "/",
                                                    "org.freedesktop.DBus.ObjectManager",
                                                    "GetManagedObjects");


    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QDBusArgument arg = response.arguments().at(0).value<QDBusArgument>();

    QMap<QString,QVariantMap> map = qdbus_cast<QMap<QString,QVariantMap>>(arg);
    for(int i=0;i<map.keys().size();i++){
        QVariantMap keys = map.value(map.keys().at(i));
        if(keys.contains("org.bluez.Device1")){

            QDBusInterface nm2 ("org.bluez", map.keys().at(i),
                                "org.bluez.Device1", QDBusConnection::systemBus());


            BtDevice *device=new BtDevice(this);
            device->setObjectPath(map.keys().at(i));
            device->setConnectedDeviceList(&connectedDevice);
            device->setConnected(nm2.property("Connected").toBool());
            device->setDeviceName(nm2.property("Name").toString());
            allDevice.insert(map.keys().at(i),device);


        }

    }
    showTray();
    QDBusConnection::systemBus().connect("org.bluez","/",
                                         "org.freedesktop.DBus.ObjectManager", "InterfacesRemoved", this,
                                         SLOT(InterfacesRemoved(QDBusObjectPath,QStringList)));
    QDBusConnection::systemBus().connect("org.bluez","/",
                                         "org.freedesktop.DBus.ObjectManager", "InterfacesAdded", this,
                                         SLOT(InterfacesAdded(QDBusObjectPath,QVariantMap)));


}

void BluetoothManager::init()
{

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.environment");
    conn.connect("", "/TrayIcons", "com.kos.environment","runningChanged",this,SLOT(showTray()));
    conn.connect("", "/TrayIcons", "com.kos.environment","koscmanagerClicked23",this,SLOT(clicked()));
    conn.connect("", "/TrayIcons", "com.kos.environment","koscmanagerLongPress23",this,SLOT(longPress()));

    QDBusConnection::systemBus().connect("org.bluez",  "/org/bluez/hci0",
                                         "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
                                         SLOT(stateChanged(QString, QVariantMap, QStringList)));



}

void BluetoothManager::exposeDBusApi()
{

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }






    session.connect("", "/ConnectedDevices", "com.kos.btmanager", "size", this, SLOT(size()));
    session.connect("", "/ConnectedDevices", "com.kos.btmanager", "get", this, SLOT(get(int)));
    session.connect("", "/ConnectedDevices", "com.kos.btmanager", "setPower", this, SLOT(setPower(bool)));
    session.connect("", "/ConnectedDevices", "com.kos.btmanager", "setAlias", this, SLOT(setAlias(QString)));


    if(!session.registerObject("/ConnectedDevices", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.btmanager")) {
        qFatal("Cannot registerService.");
        return;
    }
}



void BluetoothManager::clicked()
{
    QDBusInterface nm2 ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    bool powered = nm2.property("Powered").toBool();
    nm2.setProperty("Powered",!powered);



}

void BluetoothManager::showTray()
{

    QDBusInterface nm2 ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    bool powered = nm2.property("Powered").toBool();
    if(powered){
        icon.show(&connectedDevice);
    }else{

        icon.show("","bluetooth",23002);
        //icon.close();
    }

}

void BluetoothManager::stateChanged(QString interface_name, QVariantMap changed_properties, QStringList invalidated_properties)
{
    Q_UNUSED(interface_name);
    Q_UNUSED(invalidated_properties);

    if(changed_properties.contains("Powered")){
        bool powered = changed_properties.value("Powered").toBool();
        if(powered){
            icon.show(&connectedDevice);
        }else{
            icon.show("","bluetooth",23002);

        }
    }

}

void BluetoothManager::longPress()
{
    QStringList args;
     args<<"Bluetooth-page.qml";
       args << "-platform";
       args << "wayland-egl";
    QProcess::startDetached("KSettings",args);
}

int BluetoothManager::size()
{
    return connectedDevice.size();
}

QString BluetoothManager::get(int index)
{
    if(index < 0 || index >=connectedDevice.size()) return "";
    return connectedDevice.at(index);
}

void BluetoothManager::setPower(bool power)
{
    QDBusInterface nm2 ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    nm2.setProperty("Powered",power);
}

void BluetoothManager::setAlias(QString alias)
{
    QDBusInterface nm2 ("org.bluez", "/org/bluez/hci0","org.bluez.Adapter1", QDBusConnection::systemBus());
    nm2.setProperty("Alias",alias);
}

void BluetoothManager::InterfacesRemoved(QDBusObjectPath path, QStringList list)
{

    if(list.size() > 2){
        if(list.at(2).compare("org.bluez.Device1")==0){
            allDevice.remove(path.path());
        }
    }

    // BtDevice *device=new BtDevice(this);
    //device->setObjectPath(path.path());
    //device->setConnected(nm2.property("Connected").toBool());
    //connectedDevice.append(device);


}

void BluetoothManager::InterfacesAdded(QDBusObjectPath path, QVariantMap list)
{
    if(list.contains("org.bluez.Device1")){
        QDBusInterface nm2 ("org.bluez", path.path(),
                            "org.bluez.Device1", QDBusConnection::systemBus());


        if(allDevice.contains(path.path())){
            return;
        }
        BtDevice *device=new BtDevice(this);
        device->setObjectPath(path.path());
        device->setConnectedDeviceList(&connectedDevice);
        device->setConnected(nm2.property("Connected").toBool());
        device->setDeviceName(nm2.property("Name").toString());
        allDevice.insert(path.path(),device);
    }

}
