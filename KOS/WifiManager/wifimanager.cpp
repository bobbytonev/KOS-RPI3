#include "wifimanager.h"

wifimanager::wifimanager()
{
    QDBusConnection conn =QDBusConnection::systemBus();

    conn.connect("", "/TrayIcons", "com.kos.environment","runningChanged",this,SLOT(init()));
    conn.connect("", "/TrayIcons", "com.kos.environment","koswifitrayClicked33",this,SLOT(clicked()));
    conn.connect("", "/TrayIcons", "com.kos.environment","koswifitrayLongPress33",this,SLOT(longPress()));


    QDBusMessage message =QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons",
                                                         "","running");
    QList<QVariant> arguments;
    QDBusMessage returnVar =QDBusConnection::systemBus().call(message);
    QList<QVariant> list  =returnVar.arguments();
    if(returnVar.errorName().isEmpty())
        if(list.first().toBool())
            init();

    registerDbus();

}

wifimanager::~wifimanager()
{
    qDeleteAll(services);
}
void wifimanager::setPowered(bool powered)
{

    QDBusMessage message =QDBusMessage::createMethodCall("net.connman","/net/connman/technology/wifi",
                                                         "net.connman.Technology","SetProperty");
    QList<QVariant> arguments;
    arguments<<"Powered"<< QVariant::fromValue(QDBusVariant(powered));
    message.setArguments(arguments);
    QDBusConnection::systemBus().asyncCall(message);



}

bool wifimanager::powered()
{
    return m_powered;
}


void wifimanager::getServices()
{



    if(!services.isEmpty()){qDeleteAll(services);services.clear();}

    QDBusMessage m = QDBusMessage::createMethodCall(DBUS_NAME,
                                                    "/",
                                                    DBUS_INTERFACE,
                                                    "GetServices");


    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QDBusArgument arg = response.arguments().at(0).value<QDBusArgument>();

    QMap<QDBusObjectPath,QVariantMap> map = qdbus_cast<QMap<QDBusObjectPath,QVariantMap>>(arg);

    for(int i=0;i<map.size();i++){
        QVariantMap wifiMap = map.value(map.keys().at(i));

        if(wifiMap.value("Type").toString().compare("wifi") == 0){
            addService(map.keys().at(i).path(),wifiMap);


        }

    }
    QDBusConnection conn =QDBusConnection::systemBus();
    conn.connect("net.connman","/",
                 "net.connman.Manager", "ServicesChanged", this,
                 SLOT(ServicesChanged(QList<QVariant>,QList<QDBusObjectPath>,QDBusMessage)));
    conn.connect("net.connman","/net/connman/technology/wifi",
                 "net.connman.Technology", "PropertyChanged", this,
                 SLOT(techPropertyChanged(QString,QDBusVariant)));


}

void wifimanager::removeService(QString path)
{
    delete services.value(path);
    services.remove(path);
}

void wifimanager::addService(QString path, QVariantMap map)
{
    // Q_UNUSED(map);
    //Q_UNUSED(path);
    if(services.contains(path)) return;

    WifiService* wifiService = new WifiService(path,map.value("State").toString()
                                               ,map.value("Name").toString(),
                                               map.value("Strength").toInt());
    wifiService->setParent(this);
    services.insert(path,wifiService);
}

void wifimanager::getTechnologies()
{
    QDBusMessage m = QDBusMessage::createMethodCall(DBUS_NAME,
                                                    "/",
                                                    DBUS_INTERFACE,
                                                    "GetTechnologies");


    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QDBusArgument arg = response.arguments().at(0).value<QDBusArgument>();

    QMap<QDBusObjectPath,QVariantMap> map = qdbus_cast<QMap<QDBusObjectPath,QVariantMap>>(arg);

    for(int i=0;i<map.size();i++){
        QVariantMap wifiMap = map.value(map.keys().at(i));
        if(wifiMap.value("Type").toString().compare("wifi") == 0){
            m_powered = wifiMap.value("Powered").toBool();

            int trayId = m_powered ? 33202 : 33002;
            icon.show("","network-wireless",trayId);

        }
    }


}

void wifimanager::registerDbus()
{
    QDBusConnection session = QDBusConnection::sessionBus();
    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }
    session.connect("", "/", "com.kos.wifistate", "powered", this, SLOT(powered()));



    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.wifistate")) {
        qFatal("Cannot registerService.");
        return;
    }
}

bool wifimanager::setServiceArray(QList<ServiceArray> &list, const QDBusMessage &message)
{

    const QDBusArgument &args= message.arguments().first().value<QDBusArgument>();

    args.beginArray();
    list.clear();

    while( !args.atEnd()){
        if(args.currentType() != QDBusArgument::StructureType) return false;

        ServiceArray array;
        args.beginStructure();
        args >>array.path >>array.map;
        args.endStructure();
        list.append(array);
    }
    args.endArray();

    return true;
}



void wifimanager::ServicesChanged(QList<QVariant> vlist, QList<QDBusObjectPath> servicesRemoved, QDBusMessage message)
{
    Q_UNUSED(vlist);

    for(int i=0;i<servicesRemoved.size();i++){
        removeService(servicesRemoved.at(i).path());
    }



    QList<ServiceArray> list;
    if(!setServiceArray(list,message))return;


    for(int i=0;i<list.size();i++){
        QVariantMap wifiMap =list.at(i).map;

        if(services.contains(list.at(i).path.path())) continue;

        if(wifiMap.value("Type").toString().compare("wifi") == 0){
            addService(list.at(i).path.path(),wifiMap);
        }
    }






}

void wifimanager::techPropertyChanged(QString name, QDBusVariant var)
{

    if(name.compare("Powered") == 0){
        bool powered = var.variant().toBool();
        if(powered){
            icon.show("","network-wireless",33202);


        }else{
            icon.show("","network-wireless",33002);
        }
        m_powered = powered;
    }

}


void wifimanager::clicked()
{
    int trayId = !m_powered ? 33202 : 33002;
    icon.show("","network-wireless",trayId);
    setPowered(!m_powered);

    m_powered = !m_powered;
}

void wifimanager::longPress()
{
    QStringList args;
    args<<"Wi-Fi-page.qml";
    args << "-platform";
    args << "wayland-egl";
    QProcess::startDetached("KSettings",args);
}

void wifimanager::init()
{
    icon.restTrayId();
    getTechnologies();
    getServices();
}

