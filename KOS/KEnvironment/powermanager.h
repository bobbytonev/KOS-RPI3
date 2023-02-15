#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
class PowerManager : public QObject
{
    Q_OBJECT
public:
    PowerManager();

    Q_INVOKABLE void reboot();
    Q_INVOKABLE void shutdown();




};

#endif // POWERMANAGER_H
