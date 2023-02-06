#include "clock.h"

Clock::Clock()
{

    loadSettings();
    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/", "com.kos.clockmanager", "setTimeDate", this, SLOT(setTimeDate(long long)));
    session.connect("", "/", "com.kos.clockmanager", "changeTimeZone", this, SLOT(changeTimeZone(QString)));

    session.connect("", "/", "com.kos.clockmanager", "setApFormat", this, SLOT(setApFormat(bool)));
    session.connect("", "/", "com.kos.clockmanager", "getApFormat", this, SLOT(getApFormat()));

    session.connect("", "/", "com.kos.clockmanager", "setNtp", this, SLOT(setNtp(bool)));
    session.connect("", "/", "com.kos.clockmanager", "getNtp", this, SLOT(getNtp()));

    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.clockmanager")) {
        qFatal("Cannot registerService.");
        return;
    }

}

void Clock::sendDBusSignal(QString signal,QVariant value)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.clockmanager", signal);
    QList<QVariant> list;
    list.append(value);
    m.setArguments(list);
    session.send(m);
}

void Clock::saveToSettings(QString key, QVariant value)
{
    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"clock-manager", "clock");

    settings.beginGroup("DateTime");
    settings.setValue(key,value);
    settings.endGroup();
    settings.sync();

}

void Clock::loadSettings()

{
    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"clock-manager", "clock");
    settings.beginGroup("DateTime");
    m_apFormat = settings.value("ApFormat").toBool();
    m_ntp = settings.value("Ntp").toBool();
    if(m_ntp) ntpServer.setNtp(true);
    settings.endGroup();

    sendDBusSignal("FormatChanged",m_apFormat);


}

void Clock::changeTimeZone(QString zone)
{


    int res =unlink("/etc/localtime");
    Q_UNUSED(res);
    QString zonePath = "/etc/localtime";
    QString newZone ="/usr/share/zoneinfo/"+zone;
    int symlingResult =symlink(newZone.toStdString().c_str(), zonePath.toStdString().c_str());

    Q_UNUSED(symlingResult);

}

void Clock::setTimeDate(long long miliseconds)
{

    struct timespec tm;
    tm.tv_sec=miliseconds;
    tm.tv_nsec=0;
    int result =clock_settime(CLOCK_REALTIME,&tm);

    Q_UNUSED(result);

}
void Clock::setApFormat(bool apFormat)
{
    if(m_apFormat != apFormat ){
        m_apFormat = apFormat;

        sendDBusSignal("FormatChanged",m_apFormat);
        saveToSettings("ApFormat",apFormat);
    }

}

bool Clock::getApFormat()
{

    return m_apFormat;
}

void Clock::setNtp(bool ntp)
{

    if(m_ntp == ntp) return;
    m_ntp = ntp;
    ntpServer.setNtp(ntp);


    sendDBusSignal("NtpChanged",ntp);
    saveToSettings("Ntp",ntp);
}

bool Clock::getNtp()
{
    return m_ntp;
}
