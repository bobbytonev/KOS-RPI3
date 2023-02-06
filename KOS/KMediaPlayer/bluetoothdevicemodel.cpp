#include "bluetoothdevicemodel.h"

BluetoothDeviceModel::BluetoothDeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{
    activate();
}



int BluetoothDeviceModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return size();
}

QHash<int, QByteArray> BluetoothDeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ObjectPath] = "objectPath";
    roles[Icon] ="icon";
    roles[Name]="name";

    return roles;
}

Qt::ItemFlags BluetoothDeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}



QVariant BluetoothDeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //AudioItem item = audioList.at(index.row());
    QString objectPath =get(index.row());
    switch (role) {
    case ObjectPath:
        return objectPath;
    case Icon:
        return getIcon(objectPath);
    case Name:
        return getName(objectPath);
    default:
        return QVariant();

    }
}

void BluetoothDeviceModel::activate()
{


    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"com.kos.btmanager");
    conn.connect("", "/ConnectedDevices", "com.kos.btmanager","deviceAdded",this,SLOT(deviceAdded(QString)));

    conn.connect("", "/ConnectedDevices", "com.kos.btmanager","deviceRemoved",this,SLOT(deviceRemoved(int)));
}

QString BluetoothDeviceModel::getIcon(QString objectPath) const
{
    QDBusInterface interface ("org.bluez", objectPath,
                           "org.bluez.Device1", QDBusConnection::systemBus());


    return interface.property("Icon").toString();
}

QString BluetoothDeviceModel::getName(QString objectPath) const
{
    QDBusInterface interface ("org.bluez", objectPath,
                                    "org.bluez.Device1", QDBusConnection::systemBus());


    return interface.property("Name").toString();
}

QString BluetoothDeviceModel::get(int index) const
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.btmanager","/ConnectedDevices","","get");
    QList<QVariant> args;
    args<<index;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::sessionBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toString();
    }
    return "";

}

int BluetoothDeviceModel::size() const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.btmanager","/ConnectedDevices","","size");
    QList<QVariant> args;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::sessionBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        return list.at(0).toInt();
    }
    return -1;
}

void BluetoothDeviceModel::sendCommand(QString command, QString objectPath)
{
    QDBusInterface interface ("org.bluez", objectPath+"/player0",
                              "org.bluez.MediaPlayer1", QDBusConnection::systemBus());


    interface.asyncCall(command);
}

void BluetoothDeviceModel::deviceAdded(QString path)
{
    if(!path.isEmpty() ){
        const int index =size()-1;
        beginInsertRows(QModelIndex(),index,index);
        endInsertRows();

    }
}

void BluetoothDeviceModel::deviceRemoved(int index)
{
    beginRemoveRows(QModelIndex(),index,index);
    endRemoveRows();
}
