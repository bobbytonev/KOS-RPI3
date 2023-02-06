#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>

class VolumeControl :  public QObject
{
    Q_OBJECT

    Q_PROPERTY(double max READ max NOTIFY maxChanged)

    Q_PROPERTY(double min READ min NOTIFY minChanged)

    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)


    void setAlsaVolume(long volume);
    long getProperty(QString property);







signals:
    void volumeChanged();
    void minChanged();
    void maxChanged();

public slots:
    void volumeUpdated(qint32 volume);



public:
    VolumeControl();
    ~VolumeControl();

    double max();
    double min() ;
    double volume();
    void setVolume(const long &a);





private:
    long m_max=-1,m_min=0,m_volume;
    bool m_singleMedia;



};

#endif // VOLUMECONTROL_H
