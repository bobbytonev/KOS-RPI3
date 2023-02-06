#include "trayicon.h"

void TrayIcon::sendSignal(QString signal,QString objectPath)
{
    QDBusMessage m =QDBusMessage::createSignal(objectPath,"com.kos.environment",signal);
    QDBusConnection::systemBus().send(m);


}

int TrayIcon::trayId()
{
    return item.trayId;
}

void TrayIcon::setTrayId(int trayId)
{
    if(item.trayId != trayId){
        item.trayId = trayId;
        emit trayIdChanged(m_index);
    }
}

QString TrayIcon::imagePath()
{
    return item.imagePath;
}

void TrayIcon::setImagePath(QString imagePath)
{

    if(item.imagePath != imagePath){
        item.imagePath = imagePath;
        emit imagePathChanged(m_index);
    }
}

QString TrayIcon::text()
{
    return item.text;
}

void TrayIcon::setText(QString text)
{
    if(item.text != text){
        item.text = text;

        emit textChanged(m_index);
    }
}

QStringList TrayIcon::menus()
{
    return item.menus;
}

void TrayIcon::setObjectPath(QString objectPath)
{
    item.objectPath = objectPath;
    registerDBus();
}

QString TrayIcon::objectPath()
{
    return item.objectPath;
}

void TrayIcon::setMenus(QStringList menus)
{
    item.menus = menus;
    emit menusChanged(m_index);
}

void TrayIcon::registerDBus()
{

    QString path = item.objectPath;


    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.environment");


    session.connect("", path, "com.kos.environment", "trayIdChanged", this, SLOT(setTrayId(int)));
    session.connect("", path, "com.kos.environment", "textChanged", this, SLOT(setText(QString)));
    session.connect("", path, "com.kos.environment", "imagePathChanged", this, SLOT(setImagePath(QString)));
    session.connect("", path, "com.kos.environment", "menusChanged", this, SLOT(setMenus(QStringList)));
    getProperties();

}
void TrayIcon::getProperties(){
    setTrayId(callMethod("getTrayId").toBool());
    setText(callMethod("getText").toString());
    setImagePath(callMethod("getImagePath").toString());
    setMenus(callMethod("getMenus").toStringList());

}

QVariant TrayIcon::callMethod(QString method)
{
    QDBusMessage m =QDBusMessage::createMethodCall("com.kos.environment",item.objectPath,"", method);

    QDBusMessage response = QDBusConnection::systemBus().call(m);
    return response.arguments().first();

}

void TrayIcon::setIndex(int index)
{
    m_index = index;
}

int TrayIcon::index()
{
    return m_index;
}

TrayIcon::TrayIcon()
{
    this->moveToThread(&thread);
    thread.start();
}
