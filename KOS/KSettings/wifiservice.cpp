#include "wifiservice.h"

WifiService::WifiService()
{

}

QString WifiService::wifiPath()
{
    return m_wifiPath;
}

void WifiService::setWifiPath(QString wifiPath){
    m_wifiPath =wifiPath;


    QDBusConnection::systemBus().connect("net.connman",wifiPath,
                                         "net.connman.Service", "PropertyChanged", this,
                                         SLOT(PropertyChanged(QString,QDBusVariant)));
}

QString WifiService::security()
{
    return m_security;
}

void WifiService::setSecurity(QString security)
{
    if(m_security !=security){
        m_security = security;
        emit securityChanged();
    }
}

void WifiService::makeConnection()
{
    QDBusMessage m = QDBusMessage::createMethodCall("net.connman",
                                                    m_wifiPath,
                                                    "net.connman.Service",
                                                    "Connect");

    QDBusConnection::systemBus().asyncCall(m);
}

void WifiService::remove()
{
    QDBusMessage m = QDBusMessage::createMethodCall("net.connman",
                                                    m_wifiPath,
                                                    "net.connman.Service",
                                                    "Remove");

    QDBusConnection::systemBus().asyncCall(m);
}

void WifiService::disconnect()
{
    QDBusMessage m = QDBusMessage::createMethodCall("net.connman",
                                                    m_wifiPath,
                                                    "net.connman.Service",
                                                    "Disconnect");

    QDBusConnection::systemBus().asyncCall(m);
}


QString WifiService::name()
{
    return m_name;
}

void WifiService::setName(QString name){
    if(m_name != name){
        m_name =name;
        emit nameChanged();
    }
}

QString WifiService::state(){
    return m_state;

}
void WifiService::setState(QString state){
    if(m_state != state){
        m_state = state;
        emit stateChanged();
    }
}

int WifiService::strength(){
    return m_strength;
}
void WifiService::setStrength(int strength){
    if(m_strength != strength){
        m_strength = strength;
        emit strengthChanged();
    }
}
void WifiService::PropertyChanged(QString name, QDBusVariant var)
{
    if(name.compare("State") == 0){
        QString state = var.variant().toString();
        setState(state);
    }else if(name.compare("Strength") == 0){
        int strength =(int)var.variant().toUInt();
        setStrength(strength);
    }else if(name.compare("Security") == 0){
            QStringList securities = var.variant().toStringList();
            qDebug()<<securities.size();
            setSecurity(securities.contains("none") ? "none" : "psk");
        }
}
