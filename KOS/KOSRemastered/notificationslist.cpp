#include "notificationslist.h"

NotificationsList::NotificationsList()
{

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus system bus.");
        return;
    }


    session.connect("", "/Notifications", "com.kos.environment", "showNotification", this, SLOT(showTrayIcon(QString,int,QString,QString)));
    session.connect("", "/Notifications", "com.kos.environment", "showCustomNotification", this, SLOT(showCustomTrayIcon(QString,int,QString)));

    session.connect("", "/Notifications", "com.kos.environment", "close", this, SLOT(close(QString,int)));



    if(!session.registerObject("/Notifications", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.-Notify");
        return;
    }

    if(!session.registerService("com.kos.environment")) {
        qFatal("Cannot registerService-Notify.");
        return;
    }
}
int NotificationsList::dublicate(QString appName, int notifyId)
{

    int index = -1;

    for(int i=0;i < notifications.size();i++){
        NotificationItem item = notifications.at(i);
        if(item.appName.compare(appName) == 0 && item.notifyId == notifyId){
            index = i;
            break;
        }

    }

    return index;
}

QVector<NotificationItem> NotificationsList::items()
{
    return notifications;
}

bool NotificationsList::setItemAt(int index, const NotificationItem &item)
{
    if(index < 0 || index >= notifications.size())
        return false;


    const NotificationItem &oldItem = notifications.at(index);
    if(oldItem.priority == item.priority && oldItem.title == item.title
            && oldItem.text == item.text && oldItem.imagePath == item.imagePath
            && oldItem.buttons == item.buttons)
        return false;

    notifications[index] = item;
    return true;
}

void NotificationsList::clearAll()
{
        notifications.clear();
}

void NotificationsList::removeItemAt(int index)
{
    if( index >= 0 && index < notifications.size() ){
        emit preNotificationRemoved(index);
        notifications.remove(index);
        emit postNotificationRemoved();
    }

}




bool NotificationsList::sendSignal(QString appName,int notifyId,QString signalName)
{
    QStringList splitList = appName.split(".");
    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/Notifications","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(notifyId));
    return session.send(m);


}

bool NotificationsList::sendButtonSignal(int index, QString appName, int notifyId, QString signalName)
{
    QStringList splitList = appName.split(".");

    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/Notifications","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(notifyId));
    QList<QVariant> args;
    args.append(index);
    m.setArguments(args);
    return session.send(m);

}

void NotificationsList::showNotification(QString appName, int notifyId, int priority, QString title, QString imagePath, QString text, QStringList buttons)
{


    int index =dublicate(appName,  notifyId);
    NotificationItem item;
    item.appName=appName;
    item.notifyId = notifyId;
    item.priority=priority;
    item.title=title;
    item.imagePath = imagePath;
    item.imageProvider = !imagePath.startsWith("file:///");
    item.text=text;
    item.buttons=buttons;



    if(index > -1){

        if(setItemAt(index,item)){
            emit notificationChanged(index);

        }
    }else{
        emit preNotificationAppended();
        notifications.append(item);
        emit postNotificationAppended();

    }



}

void NotificationsList::showCustomNotification(QString appName, int notifyId, int priority, QString qmlFilePath)
{
    NotificationItem item;
    item.appName=appName;
    item.notifyId=notifyId;
    item.qmlPath=qmlFilePath;
    item.priority = priority;

    emit preNotificationAppended();
    notifications.append(item);
    emit postNotificationAppended();
}

int NotificationsList::close(QString appName, int notifyId)
{
    int index = dublicate( appName,  notifyId);

    if(index > -1 ){
        emit preNotificationRemoved(index);
        notifications.remove(index);
        emit postNotificationRemoved();
    }
    return index;
}


