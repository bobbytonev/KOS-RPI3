#ifndef NOTIFICATIONSLIST_H
#define NOTIFICATIONSLIST_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>



//0 - Low
//1 - Normal
//2 - Medium
//3 - High
//4 - Ultra

struct NotificationItem
{

    QString appName,imagePath,title,text="",qmlPath="";
    int notifyId;
    int priority=1;
    bool imageProvider;
    QStringList buttons={};

};
class NotificationsList :public QObject
{

    Q_OBJECT


public:

    NotificationsList();

    int dublicate(QString appName,int notifyId);
    QVector<NotificationItem> items();
    bool setItemAt(int index,const NotificationItem &item);
    void clearAll();
    Q_INVOKABLE void removeItemAt(int index);
    Q_INVOKABLE bool sendSignal(QString appName,int notifyId,QString signalName);
    Q_INVOKABLE bool sendButtonSignal(int index,QString appName,int notifyId,QString signalName);



signals:
    void preNotificationRemoved(int index);
    void postNotificationRemoved();
    void preNotificationAppended();
    void postNotificationAppended();
    void notificationChanged(int index);

public slots:

    Q_SCRIPTABLE void showNotification(QString appName,int notifyId,int priority,QString title,QString imagePath,QString text,QStringList buttons={});
    Q_SCRIPTABLE void showCustomNotification(QString appName,int notifyId,int priority,QString qmlFilePath);
    Q_SCRIPTABLE int close(QString appName,int notifyId);





private:
    QVector<NotificationItem> notifications;
    QDBusConnection session = QDBusConnection::systemBus();
};

#endif // NOTIFICATIONSLIST_H
