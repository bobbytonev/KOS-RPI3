#ifndef HWCLOCK_H
#define HWCLOCK_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QProcess>
#include <QDateTime>
#include <QTimeZone>
#include <QFile>
#include <QTextStream>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
class hwclock : public QObject
{
    Q_OBJECT



public:
    Q_PROPERTY(bool apFormat READ apFormat WRITE setApFormat NOTIFY apFormatChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool ntp READ ntp WRITE setNtp NOTIFY ntpChanged)



    hwclock();

    bool apFormat() const ;
    void setApFormat(const bool &a);

    bool active() const ;
    void setActive(const bool &a);



    void setNtp(bool ntp);
    bool ntp();

    void getAp();
    void getNtp();

    Q_INVOKABLE void setTimeDate(QString timedate,bool time);


signals:
    void apFormatChanged();
    void activeChanged();
    void ntpChanged();


private:
    bool m_apFormat;
    bool m_active;
    bool m_ntp;





};

#endif // HWCLOCK_H
