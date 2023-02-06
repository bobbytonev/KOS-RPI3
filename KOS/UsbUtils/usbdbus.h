#ifndef USBDBUS_H
#define USBDBUS_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
class UsbDbus : public QObject
{
    Q_OBJECT
public:
    UsbDbus();
    void registerDbus();
    void setUsbList(QMap<QString,QStringList>* usbList);

public slots:
    Q_SCRIPTABLE QStringList get(int index);
    Q_SCRIPTABLE int size();
    void sendSingnal(QString signalName,QList<QVariant> arrgs);
private:
    QMap<QString,QStringList>* m_usbList = NULL;
    QDBusConnection session =QDBusConnection::systemBus();

};

#endif // USBDBUS_H
