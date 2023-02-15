#include "volumecontrol.h"
double VolumeControl::max()
{
    return m_max;
}

double VolumeControl::min()
{
    return m_min;
}

double VolumeControl::volume()
{



    return m_volume;
}

void VolumeControl::setVolume(const long &a)
{
    if(m_volume!=a)
    {
        m_volume=a;
        setAlsaVolume(m_volume);
        emit volumeChanged();
    }

}

void VolumeControl::setAlsaVolume(long volume)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.audiomanager","/Volume", "", "setVolume");
    QList<QVariant> args;
    qint32 vol = volume;
    args<<vol;
    m.setArguments(args);

    qDebug()<<QDBusConnection::sessionBus().call(m);


}

long VolumeControl::getProperty(QString property)
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.audiomanager","/Volume", "", property);
    QDBusMessage response = QDBusConnection::sessionBus().call(m);


    QList<QVariant> list =response.arguments();
    if(list.size() > 0){
        return list.at(0).toInt();

    }

    return -1;
}


void VolumeControl::volumeUpdated(qint32 volume)
{
    if(m_volume !=volume){
        m_volume = volume;
        emit volumeChanged();
    }

}

void VolumeControl::runningSignal()
{
    m_volume = getProperty("getVolume");
    //m_max = getProperty("getMax");
    //m_min = getProperty("getMin");

    emit volumeChanged();



}

VolumeControl::VolumeControl()
{

    m_volume = getProperty("getVolume");
    runningSignal();
    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"com.kos.audiomanager");

    conn.connect("", "/Volume", "com.kos.audiomanager","runningChanged",this,SLOT(runningSignal()));
    conn.connect("", "/Volume", "com.kos.audiomanager","volumeChanged",this,SLOT(volumeUpdated(qint32)));


}

VolumeControl::~VolumeControl()
{

}




