#ifndef HWCLOCK_H
#define HWCLOCK_H
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QObject>

class HwClock: public QObject
{
    Q_OBJECT
public:
    HwClock();
    Q_PROPERTY(bool apFormat READ apFormat NOTIFY apFormatChanged)

   void setApFormat(bool apFormat);
   bool apFormat();

signals:
    void apFormatChanged();

public slots:
    void updateApFormat(bool apFormat);

private:
    bool m_apFormat;


};

#endif // HWCLOCK_H
