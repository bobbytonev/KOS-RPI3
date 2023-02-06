#ifndef USBUTILS_H
#define USBUTILS_H

#include <QObject>
#include <QThread>
#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <sys/mount.h>
#include <QDir>
#include "trayicon.h"
#include "usbdbus.h"
#include "language.h"
//formula
//11 - number of butes per sector //2 bytes
//13 - number of sectors per cluster //1 bytes
//14 - reserved sectors //2 bytes
//16 - number of FATs //1 byte
//36 - number of sectors per FAT
//44 - number of root cluster

class usbutils : public QThread
{
    Q_OBJECT
     struct BootSector{
        short bytesPerSector;
        char numberOfSectorsPerCluster;
        short reservedSectors;
        char numberOfFATs;
        int numberOfSectorsPerFat;
        int numberOfRootCluster;
    };
public:
    usbutils();
    void run() override;
    void mountOnBoot();

    void add(QString partition, bool firstTime);
    void eject(QString partition);
    QString createMoutingPoint(QString partition);
    void registerDBus();
    QMap<QString,QStringList> getUsbList();
    QString getDeviceName(QString partition);


    //void preItemAdded();
    //void postItemAdded();
signals:
    void sizeChanged(int size);
    void emitDbusSignal(QString signalName,QList<QVariant> arrgs);

public slots:
    Q_SCRIPTABLE int size();
    void menuClicked(int index);
    void init();
    void updateTrayIconLanguage();




private:
    QMap<QString,QStringList> usbList;
    TrayIcon icon;
    UsbDbus dbus;
    Language lang;
    QDBusConnection session = QDBusConnection::systemBus();



};

#endif // USBUTILS_H
