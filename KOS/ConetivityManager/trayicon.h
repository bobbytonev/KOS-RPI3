#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QtDBus/QtDBus>


class TrayIcon : public QObject
{
    Q_OBJECT

public:

    TrayIcon();
    void show(QStringList* connectionList);
    void updateIcon(QString imagePath);
    void show(QString text, QString imagePath, int tray_id);
    QString getName(QString objectPath);
    void close();
    bool isPowered();



private:

    const QString APP_NAME = "com.kos.cmanager";
    int TRAY_ID = 23000;

    //2301

    //third digit from last
    //2 - make button checked
    //1 - disable checking
    //0 - make button unchecked

    //second digit from last
    //0 - show text on drop down and tray
    //1 - show text only on tray
    //2 - show text only on drop down


    //last digit
    //0 - show on drop down and tray
    //1 - show only on tray
    //2 - show only on drop down


};

#endif // TRAYICON_H
