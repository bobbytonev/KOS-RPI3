#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <QObject>
#include "trayicon.h"
struct WifiServiceItem{
    QString state;
    QString name;
    int strenght;
    QString objectPath;
};

class WifiService : public QObject
{
    Q_OBJECT
public:
    WifiService(QString objectPath,QString state,QString name,int strenght);

    WifiServiceItem getItem();
    void setState(QString state,bool firstRun);
    void setName(QString name);
    void setStrenght(int strenght);

    void showTray();
public slots:
    void PropertyChanged(QString name,QDBusVariant var);


private:
    WifiServiceItem item;
    TrayIcon icon;
    int lastImage = -1;
};

#endif // WIFISERVICE_H
