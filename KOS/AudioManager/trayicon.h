#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>

class TrayIcon : public QObject
{
    Q_OBJECT

public:

    TrayIcon();
    void show(QString text,QString imagePath);
    void updateIcon(QString imagePath);
    void setMax(long max);
    void setFirstRun(bool firstRun);
    void setText(QString text);
    void setImage(QString image);
public slots:
    void volumeChanged(qint32 volume);

private:
    long m_max;
    bool m_firstRun = true;
    const QString APP_NAME = "com.kos.audiomanager";
    const QString TRAY_PATH = "/com/kos/tray_com_kos_audiomanager_67";
    const int TRAY_ID = 67011;
    int lastImage =-1;


};

#endif // TRAYICON_H
