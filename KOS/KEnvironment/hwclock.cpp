#include "hwclock.h"

HwClock::HwClock()
{

    //getApFormat

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.clockmanager");
    conn.connect("", "/", "com.kos.clockmanager","FormatChanged",this,SLOT(updateApFormat(bool)));

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.clockmanager","/", "", "getApFormat");

    QDBusMessage response =conn.call(m);
    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        m_apFormat =list.at(0).toBool();
        emit apFormatChanged();


    }

}

void HwClock::setApFormat(bool apFormat)
{
    if(m_apFormat != apFormat){
        m_apFormat = apFormat;
        emit apFormatChanged();
    }
}



bool HwClock::apFormat()
{
    return m_apFormat;
}

void HwClock::updateApFormat(bool apFormat)
{
    setApFormat(apFormat);
}
