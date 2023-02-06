#include "wifimodel.h"
#include <QDebug>
WifiModel::WifiModel(QObject *parent)
    : QAbstractListModel(parent)
{

    activate(true);
}

int WifiModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return services.size();
}

QVariant WifiModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString key = services.keys().at(index.row());
    switch (role) {
    case ServicePath:
        return QVariant(key).toString();
    case ServiceName:
        return QVariant(services.value(key).name).toString();
    case ServiceStrength:
        return QVariant(services.value(key).strength).toUInt();
    case ServiceState:
        return QVariant(services.value(key).state).toString();
    case ServiceSecurity:
        return QVariant(services.value(key).security).toString();
    default:
        return QVariant();

    }
}

void WifiModel::activate(bool connectToSignal)
{

    QDBusMessage m = QDBusMessage::createMethodCall("net.connman",
                                                    "/",
                                                    "net.connman.Manager",
                                                    "GetServices");


    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QDBusArgument arg = response.arguments().at(0).value<QDBusArgument>();

    QMap<QDBusObjectPath,QVariantMap> map = qdbus_cast<QMap<QDBusObjectPath,QVariantMap>>(arg);

    for(int i=0;i<map.size();i++){
        QVariantMap wifiMap = map.value(map.keys().at(i));

        if(wifiMap.value("Type").toString().compare("wifi") == 0){
            createItem(map.keys().at(i).path(),wifiMap);



        }

    }
    if(connectToSignal){
        QDBusConnection conn =QDBusConnection::systemBus();
        conn.connect("net.connman","/",
                     "net.connman.Manager", "ServicesChanged", this,
                     SLOT(ServicesChanged(QList<QVariant>,QList<QDBusObjectPath>,QDBusMessage)));
    }

}

void WifiModel::scan()
{

    setState("Scanning");
    QDBusMessage m = QDBusMessage::createMethodCall("net.connman",
                                                    "/net/connman/technology/wifi",
                                                    "net.connman.Technology",
                                                    "Scan");
    QDBusConnection::systemBus().callWithCallback(m,this,SLOT(returnMethod()),SLOT(errorMethod()));

}

QString WifiModel::state()
{
    return m_state;
}
bool WifiModel::setServiceArray(QList<ServiceItem> &list, const QDBusMessage &message)
{

    const QDBusArgument &args= message.arguments().first().value<QDBusArgument>();

    args.beginArray();
    list.clear();

    while( !args.atEnd()){
        if(args.currentType() != QDBusArgument::StructureType) return false;

        ServiceItem array;
        args.beginStructure();
        args >>array.path >>array.map;
        args.endStructure();
        list.append(array);
    }
    args.endArray();

    return true;
}

void WifiModel::createItem(QString objectPath,QVariantMap vars)
{
    WifiItem item;
    item.state = vars.value("State").toString();
    item.name = vars.value("Name").toString();
    item.strength = vars.value("Strength").toUInt();

    QStringList securities = vars.value("Security").toStringList();
    item.security = securities.contains("none") ? "none" : "psk";
    services.insert(objectPath,item);
}

void WifiModel::setState(QString state)
{
    if(m_state != state){
        m_state = state;
        emit stateChanged();
    }
}

void WifiModel::returnMethod()
{

    setState("Finnished");
}

void WifiModel::errorMethod()
{
    qDebug()<<"ERROR";
    setState("Error");

}

void WifiModel::ServicesChanged(QList<QVariant> vlist, QList<QDBusObjectPath> servicesRemoved, QDBusMessage message)
{
    Q_UNUSED(vlist);
    Q_UNUSED(servicesRemoved);
    Q_UNUSED(message);
    services.clear();

    beginResetModel();
    activate(false);
    endResetModel();
}

QHash<int, QByteArray> WifiModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ServicePath] = "servicePath";
    roles[ServiceStrength] = "serviceStrength";
    roles[ServiceName] = "serviceName";
    roles[ServiceState] = "serviceState";
    roles[ServiceSecurity] = "serviceSecurity";


    return roles;
}
