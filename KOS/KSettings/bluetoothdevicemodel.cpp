#include "bluetoothdevicemodel.h"

BluetoothDeviceModel::BluetoothDeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{

    activate();
}


int BluetoothDeviceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()){

        return 0;
    }

    return btDevices.size();
}



QVariant BluetoothDeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    switch (role) {
    case DevicePath:
        return QVariant(btDevices.at(index.row())).toString();

    default:
        return QVariant();

    }
}
QHash<int, QByteArray> BluetoothDeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DevicePath] = "objectPath";


    return roles;
}
void BluetoothDeviceModel::activate()
{


    QDBusMessage m = QDBusMessage::createMethodCall("org.bluez",
                                                    "/",
                                                    "org.freedesktop.DBus.ObjectManager",
                                                    "GetManagedObjects");


    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QDBusArgument arg = response.arguments().at(0).value<QDBusArgument>();

    QMap<QString,QVariantMap> map = qdbus_cast<QMap<QString,QVariantMap>>(arg);
   beginResetModel();
    for(int i=0;i<map.keys().size();i++){
        QVariantMap keys = map.value(map.keys().at(i));
        if(keys.keys().size() > 0){
            if(keys.keys().at(0).compare("org.bluez.Device1")==0){
                btDevices.append(map.keys().at(i));

            }
        }

    }
   endResetModel();
   QDBusConnection::systemBus().connect("org.bluez","/",
                                        "org.freedesktop.DBus.ObjectManager", "InterfacesRemoved", this,
                                        SLOT(InterfacesRemoved(QDBusObjectPath,QStringList)));
   QDBusConnection::systemBus().connect("org.bluez","/",
                                        "org.freedesktop.DBus.ObjectManager", "InterfacesAdded", this,
                                        SLOT(InterfacesAdded(QDBusObjectPath,QVariantMap)));
}

Qt::ItemFlags BluetoothDeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}



void BluetoothDeviceModel::InterfacesRemoved(QDBusObjectPath path, QStringList list)
{

    if(list.size() > 2){
        if(list.at(2).compare("org.bluez.Device1")==0){
            for(int i=0;i<btDevices.size();i++){

                if(btDevices.at(i).compare(path.path())==0){
                    beginRemoveRows(QModelIndex(),i,i);
                    btDevices.removeAt(i);
                    endRemoveRows();
                    break;
                }
            }

        }
    }

}

void BluetoothDeviceModel::InterfacesAdded(QDBusObjectPath path, QVariantMap list)
{

    if(list.contains("org.bluez.Device1")){

        if(!btDevices.contains(path.path())){
            int index =btDevices.size();
            beginInsertRows(QModelIndex(),index,index);
            btDevices.append(path.path());
            endInsertRows();
        }

    }

}
