#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QtDBus/QtDBus>
class TrayIcon : public QObject
{
    Q_OBJECT
public:
    TrayIcon();
    void updateIcon(QString imagePath);
    void show(QString text, QString imagePath, int tray_id);
    void close();

    int getTrayid();

    void restTrayId();
private:
    const QString APP_NAME = "com.kos.wifitray";
    int TRAY_ID = 33002;
    int lastTray = 0;

};

#endif // TRAYICON_H
