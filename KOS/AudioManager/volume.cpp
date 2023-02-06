#include "volume.h"

#include <QProcess>

Volume::Volume()
{


    m_volume = getAlsaVolume();


    connect(&listener,SIGNAL(volumeChanged()),this,SLOT(volumeChanged()));
    connect(this,SIGNAL(volumeChangedSingnal(qint32)),&tray_icon,SLOT(volumeChanged(qint32)));
    listener.start();

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/Volume", "com.kos.audiomanager", "setVolume", this, SLOT(setVolume(qint32)));
    session.connect("", "/Volume", "com.kos.audiomanager", "getVolume", this, SLOT(getVolume()));
    session.connect("", "/Volume", "com.kos.audiomanager", "getMax", this, SLOT(getMax()));
    session.connect("", "/Volume", "com.kos.audiomanager", "getMin", this, SLOT(getMin()));



    if(!session.registerObject("/Volume", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObjects.");
        return;
    }

    if(!session.registerService("com.kos.audiomanager")) {
        qFatal("Cannot registerService.");
        return;
    }
    sendRunningSignal();

    showTray();
    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.environment");
    conn.connect("", "/TrayIcons", "com.kos.environment","runningChanged",this,SLOT(showTray()));
    conn.connect("", "/TrayIcons", "com.kos.environment","kosaudiomanagerClicked67",this,SLOT(clicked()));
    conn.connect("", "/TrayIcons", "com.kos.environment","kosaudiomanagerLongPress67",this,SLOT(longPress()));


}

long Volume::getAlsaVolume()
{
    snd_mixer_t  *handle;
    long volume=0;



    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);

    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    elem = snd_mixer_find_selem(handle, sid);

    if(m_max < 0) {
        snd_mixer_selem_get_playback_volume_range(elem, &m_min, &m_max);
        tray_icon.setMax(m_max);
    }


    snd_mixer_selem_get_playback_volume(elem,SND_MIXER_SCHN_FRONT_LEFT,&volume);

    snd_mixer_close(handle);


    return volume;

}

void Volume::setAlsaVolume(long volume)
{
    snd_mixer_t  *handle;




    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);

    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    elem = snd_mixer_find_selem(handle, sid);

    if(m_max < 0) snd_mixer_selem_get_playback_volume_range(elem, &m_min, &m_max);


    snd_mixer_selem_set_playback_volume_all(elem,volume);
    snd_mixer_close(handle);
}


void Volume::sendDbusSignal()
{
    QDBusMessage m =QDBusMessage::createSignal("/Volume","com.kos.audiomanager", "volumeChanged");
    QList<QVariant> list;
    list.append(getVolume());

    m.setArguments(list);
    session.send(m);
}

void Volume::setBalance()
{
    // char * cardName =NULL;
    //snd_card_get_name(0,&cardName);

}

void Volume::sendRunningSignal()
{
    QDBusMessage m =QDBusMessage::createSignal("/Volume","com.kos.audiomanager", "runningChanged");
    session.send(m);
}

void Volume::setVolume(qint32 volume)
{
    if(m_volume !=volume && volume >= m_min && volume <= m_max){
        m_volume =volume;
        setAlsaVolume(m_volume);
        sendDbusSignal();
        emit volumeChangedSingnal(m_volume);
    }
}

void Volume::volumeChanged()
{
    long newVolume = getAlsaVolume();
    if(m_volume !=newVolume){
        m_volume = newVolume;

        sendDbusSignal();
        emit volumeChangedSingnal(m_volume);
    }
}

void Volume::showTray()
{

    tray_icon.setFirstRun(true);
    tray_icon.volumeChanged(m_volume);
}

void Volume::clicked()
{
    if(m_volume !=0){
        previousVolume = m_volume;
        setVolume(0);
    }else{
        setVolume(previousVolume);


    }


}

void Volume::longPress()
{

}

qint32 Volume::getVolume()
{
    return m_volume;
}

qint32 Volume::getMax()
{
    return m_max;
}

qint32 Volume::getMin()
{
    return m_min;
}
