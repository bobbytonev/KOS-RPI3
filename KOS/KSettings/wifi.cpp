#include "wifi.h"

Wifi::Wifi()
{
    QDBusConnection session = QDBusConnection::systemBus();
    if (!session.isConnected())
    {
        //qFatal("Cannot connect to the D-Bus session bus.");
        //return;
    }

    session.connect("com.kos.wifiagent", OBJECT_PATH, "net.connman.Agent", "RequestInput", this,
                    SLOT(RequestInput(QDBusObjectPath,QVariantMap,const QDBusMessage& message)));

    session.connect("com.kos.wifiagent", OBJECT_PATH, "net.connman.Agent", "Cancel", this, SLOT(Cancel()));
    session.connect("com.kos.wifiagent", OBJECT_PATH, "net.connman.Agent", "ReportError", this,
                    SLOT(ReportError(QDBusObjectPath,QString)));
    session.connect("com.kos.wifiagent", OBJECT_PATH, "net.connman.Agent", "Release", this,
                    SLOT(Release()));


    if(!session.registerObject("/kos/settings/wifiagent", this, QDBusConnection::ExportScriptableContents)) {
        //qFatal("Cannot registerObject.");
        return;
    }

    getPowered();
    registerAgent();
    QDBusConnection conn =QDBusConnection::systemBus();
    conn.connect("net.connman","/net/connman/technology/wifi",
                 "net.connman.Technology", "PropertyChanged", this,
                 SLOT(PropertyChanged(QString,QDBusVariant)));

}

Wifi::~Wifi()
{
    unregisterAgent();
}



bool Wifi::powered()
{
    if(firstRun){
        firstRun =false;
        // getPowered();
    }
    return m_powered;
}

void Wifi::setPowered(bool powered)
{
    if(m_powered != powered){
        m_powered = powered;
        emit poweredChanged();
        QDBusMessage message =QDBusMessage::createMethodCall("net.connman","/net/connman/technology/wifi",
                                                             "net.connman.Technology","SetProperty");
        QList<QVariant> arguments;
        arguments<<"Powered"<< QVariant::fromValue(QDBusVariant(m_powered));
        message.setArguments(arguments);
        QDBusConnection::systemBus().asyncCall(message);
    }
}

void Wifi::getPowered()
{

    QDBusMessage message =QDBusMessage::createMethodCall("com.kos.wifistate","/",
                                                         "","powered");
   // qDebug()<<QDBusConnection::sessionBus().call(message);
    QDBusMessage reply = QDBusConnection::sessionBus().call(message);
    m_powered = reply.arguments().first().toBool();

}

QString Wifi::password()
{
    return m_password;
}

void Wifi::setPassword(QString password)
{
    m_password = password;
    emit passwordChanged();
}

void Wifi::registerAgent()
{
    QDBusMessage message =QDBusMessage::createMethodCall("net.connman","/",
                                                         "net.connman.Manager","RegisterAgent");
    QDBusObjectPath path;
    path.setPath(OBJECT_PATH);
    QList<QVariant> arguments;
    arguments<<path;
    message.setArguments(arguments);
    QDBusConnection::systemBus().asyncCall(message);
}

void Wifi::unregisterAgent()
{
    QDBusMessage message =QDBusMessage::createMethodCall("net.connman","/",
                                                         "net.connman.Manager","UnregisterAgent");
    QDBusObjectPath path;
    path.setPath(OBJECT_PATH);
    QList<QVariant> arguments;
    arguments<<path;
    message.setArguments(arguments);
    QDBusConnection::systemBus().asyncCall(message);
}

void Wifi::sendPassword()
{
    QVariantMap map;
    map.insert("Passphrase",m_password);
    replyMessage = replyMessage.createReply(map);
    QDBusConnection::systemBus().systemBus().send(replyMessage);

}

QVariantMap Wifi::RequestInput(QDBusObjectPath service, QVariantMap fields,const QDBusMessage& message)
{

    QVariantMap map;
    replyMessage = message;
    message.setDelayedReply(true);

    emit inputRequest();
    return map;
}

void Wifi::Cancel()
{
    emit cancel();
}

void Wifi::ReportError(QDBusObjectPath service, QString errorName)
{

    emit error(errorName);
}

void Wifi::Release()
{

}

void Wifi::PropertyChanged(QString name, QDBusVariant var)
{


    if(name.compare("Powered") == 0){
        bool powered = var.variant().toBool();
        m_powered =powered;
        emit poweredChanged();
    }
}

