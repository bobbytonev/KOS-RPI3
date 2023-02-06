
#ifndef STYLES_H
#define STYLES_H

#include <QObject>
#include <QSettings>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDebug>
#include <QDir>
#include <unistd.h>
#include "trayicon.h"


class Styles:public QObject
{
    Q_OBJECT
public:
    Styles();

    bool saveToSettings(QString key,QString value,bool prop);

    void loadFromSettings();

    void emitDbusSignal(QString signalName,QString message);

    void loadConfig();

    bool itemAt(QString key, QString group);

    void switchMode();



public slots:
    Q_SCRIPTABLE void setIconPackName(QString iconPack);
    Q_SCRIPTABLE QString iconPackName();
    Q_SCRIPTABLE void setAppStyleName(QString styleName);
    Q_SCRIPTABLE QString appStyleName();
    Q_SCRIPTABLE void changeProperty(QString key,QString value);
    Q_SCRIPTABLE int size();
    Q_SCRIPTABLE QStringList get(int index);

    void showTray();
    void clicked();


private:
    QString m_iconPack;
    QString m_styleName;

    bool hasDarkMode=false;
    bool darkMode=false;

    QDBusConnection session = QDBusConnection::systemBus();

    const QString STYLES_FOLDER =  "/usr/share/themes/";
    const QStringList ICONS_FOLDER =  {"/usr/share/icons/"};
    const QString GROUP_NAME = "Properties";


    QList<QStringList> themeConfig;
    TrayIcon icon;


};
#endif // STYLES_H
