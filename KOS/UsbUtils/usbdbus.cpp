#include "usbdbus.h"

UsbDbus::UsbDbus()
{


    registerDbus();

}

void UsbDbus::setUsbList(QMap<QString, QStringList> *usbList)
{
    if(m_usbList == NULL)
        m_usbList=usbList;
}

void UsbDbus::registerDbus()
{
    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/", "com.kos.usbmanager", "get", this, SLOT(get(QStringList)));
    session.connect("", "/", "com.kos.usbmanager", "size", this, SLOT(size(int)));

    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.usbmanager")) {
        qFatal("Cannot registerService.");
        return;
    }
}

void UsbDbus::sendSingnal(QString signalName, QList<QVariant> arrgs)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.usbmanager", signalName);
    QList<QVariant> list;
    list.append(arrgs);
    m.setArguments(list);
    session.send(m);
}
QStringList UsbDbus::get(int index)
{
    if(m_usbList == NULL) return QStringList{};

    if(index < 0 && index >= m_usbList->size()) return QStringList{};


    //QStringList list{usbList.keys().at(index),usbList.values().at(i).at(0)};

    return m_usbList->values().at(index);
}

int UsbDbus::size()
{
    if(m_usbList == NULL) return -1;

    return m_usbList->size();
}
