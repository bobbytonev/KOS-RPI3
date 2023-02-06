#include "hwclock.h"
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>
hwclock::hwclock()
{}

bool hwclock::apFormat() const
{
    return m_apFormat;

}

void hwclock::setApFormat(const bool &a)
{
    if(m_apFormat == a) return;

    QDBusMessage m =QDBusMessage::createMethodCall("com.kos.clockmanager","/","", "setApFormat");
    QList<QVariant> list;
    list.append(a);
    m.setArguments(list);
    QDBusConnection::systemBus().asyncCall(m);
    m_apFormat = a;
    emit apFormatChanged();




}

bool hwclock::active() const
{

    return m_active;
}

void hwclock::setActive(const bool &a)
{
    if(a==true){

        getAp();
        getNtp();

    }

    if(m_active!=a){
        m_active=a;
        emit activeChanged();
    }
}




void hwclock::getAp()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.clockmanager",
                                                    "/",
                                                    "",
                                                    "getApFormat");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();


    if(!list.isEmpty()){

        m_apFormat =list.at(0).toBool();
        emit apFormatChanged();


    }
}

void hwclock::getNtp()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.clockmanager",
                                                    "/",
                                                    "",
                                                    "getNtp");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();


    if(!list.isEmpty()){

        m_ntp =list.at(0).toBool();
        emit ntpChanged();


    }
}
void hwclock::setTimeDate(QString timedate,bool time)
{


    QDateTime dt =QDateTime::currentDateTime();
    if(time){
        timedate=dt.date().toString("dd-MM-yyyy") + " "+timedate;

    }else{

        timedate+=" "+dt.time().toString("hh:mm:ss");
    }


    QDateTime datetime =QDateTime::fromString(timedate,"dd-MM-yyyy hh:mm:ss");

    qlonglong miliseconds = datetime.toMSecsSinceEpoch()/1000;
    QDBusMessage m =QDBusMessage::createMethodCall("com.kos.clockmanager","/","", "setTimeDate");
    QList<QVariant> list;
    list.append(miliseconds);
    m.setArguments(list);
    QDBusConnection::systemBus().asyncCall(m);



}

void hwclock::setNtp(bool ntp)
{
    if(m_ntp == ntp) return;


    QDBusMessage m =QDBusMessage::createMethodCall("com.kos.clockmanager","/","", "setNtp");
    QList<QVariant> list;
    list.append(ntp);
    m.setArguments(list);
    QDBusConnection::systemBus().asyncCall(m);

    m_ntp = ntp;
    emit ntpChanged();

}

bool hwclock::ntp()
{
    return m_ntp;
}






