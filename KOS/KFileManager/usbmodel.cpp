#include "usbmodel.h"

UsbModel::UsbModel(QObject *parent)
    : QAbstractListModel(parent)
{

    activate();
}

int UsbModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return usbList.size();
}

QVariant UsbModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    UsbItem item = usbList.at(index.row());
    switch (role) {
    case moutingPoint:
        return QVariant(item.moutingPoint).toString();
    case deviceName:
        return QVariant(item.deviceName).toString();
    default:
        return QVariant();

    }


}
QHash<int, QByteArray> UsbModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[deviceName] = "deviceName";
    roles[moutingPoint] = "moutingPoint";
    return roles;
}
void UsbModel::activate()
{

    for(int i=0;i<size();i++){
        QStringList list = get(i);
        if(list.size() > 1){
            UsbItem item;
            item.moutingPoint =list.at(0);
            item.deviceName = list.at(1);
            usbList.append(item);
        }
    }

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.usbmanager");
    conn.connect("", "/", "com.kos.usbmanager","partitionInserted",this,SLOT(partitionInserted(QStringList)));
    conn.connect("", "/", "com.kos.usbmanager","partitionRemoved",this,SLOT(partitionRemoved(QStringList)));



}

QStringList UsbModel::get(int index)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.usbmanager","/","","get");
    QList<QVariant> args;
    args.append(index);
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toStringList();
    }
    return QStringList{};
}

int UsbModel::size()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.usbmanager","/","","size");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        return list.at(0).toInt();
    }

    return -1;
}

void UsbModel::partitionInserted(QStringList usb)
{

    if(usb.size() > 1){
        const int index =usbList.size();
        UsbItem item;
        item.moutingPoint = usb.at(0);
        item.deviceName = usb.at(1);
        usbList.append(item);
        beginInsertRows(QModelIndex(),index,index);
        endInsertRows();
    }


}

void UsbModel::partitionRemoved(QStringList usb)
{

    if(usb.size() < 1) return;
    int index =-1;
    for(int i=0;i<usbList.size();i++){

        UsbItem item = usbList.at(i);
        if(item.moutingPoint.compare(usb.at(0)==0)){
            usbList.removeAt(i);
            index = i ;
            break;
        }

    }
    if(index !=-1){
        beginRemoveRows(QModelIndex(),index,index);
        endRemoveRows();
    }

}
