#include "powermanager.h"

PowerManager::PowerManager()
{

}

void PowerManager::reboot()
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.powermanager","/","","restart");
    QDBusConnection::systemBus().asyncCall(m);
}

void PowerManager::shutdown()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.powermanager","/","","shutdown");
    QDBusConnection::systemBus().asyncCall(m);
}
