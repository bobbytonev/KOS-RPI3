#ifndef VOLUME_H
#define VOLUME_H

#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDebug>
#include <QObject>
//#include <QSettings>
#include "volumelistener.h"
#include "trayicon.h"
class Volume :public QObject
{
    Q_OBJECT
public:
    Volume();
    long getAlsaVolume();
    void setAlsaVolume(long volume);
    void sendDbusSignal();
    void setBalance();

    void sendRunningSignal();

signals:
    void volumeChangedSingnal(qint32 volume);

public slots:
    Q_SCRIPTABLE void setVolume(qint32 volume);
    Q_SCRIPTABLE qint32 getVolume();
    Q_SCRIPTABLE qint32 getMax();
    Q_SCRIPTABLE qint32 getMin();
    void volumeChanged();
    void showTray();
    void clicked();
    void longPress();


private:
    long m_volume,m_max=-1,m_min=0,previousVolume=0;
    QDBusConnection session = QDBusConnection::sessionBus();
    VolumeListener listener;
    snd_mixer_selem_id_t  *sid;
    snd_mixer_elem_t *elem;
    //const char* card ="default";
    const char* card ="hw:1";
    const char* selem_name="Master";
    //const char* selem_name="Headphone";
    TrayIcon tray_icon;
    QThread thread;



};

#endif // VOLUME_H
