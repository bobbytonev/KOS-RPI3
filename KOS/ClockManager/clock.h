#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QSettings>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <sys/time.h>
#include <unistd.h>
#include "QNtp.h"

class Clock : public QObject
{
    Q_OBJECT
public:
    Clock();

    void sendDBusSignal(QString signal, QVariant value);
    void saveToSettings(QString key,QVariant value);
    void loadSettings();
public slots:
    Q_SCRIPTABLE void changeTimeZone(QString zone);
    Q_SCRIPTABLE void setTimeDate(long long miliseconds);

    Q_SCRIPTABLE void setApFormat(bool apFormat);
    Q_SCRIPTABLE bool getApFormat();
    Q_SCRIPTABLE void setNtp(bool ntp);
    Q_SCRIPTABLE bool getNtp();

private:
    bool m_apFormat = false;
    bool m_ntp = false;
    QDBusConnection session =QDBusConnection::systemBus();
    QNtp ntpServer;
};

#endif // CLOCK_H
