
#ifndef TRAYICONSERVER_H
#define TRAYICONSERVER_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>

#include <QDBusObjectPath>
struct TrayIconItem
{

    QString appName,imagePath,text="",qmlPath="";
    int trayId;
    bool imageProvider = true;
    QStringList menus={};

};
class TrayIconList : public QObject
{
    Q_OBJECT

public:
    TrayIconList();

    int dublicate(QString appName,int trayId);
    QVector<TrayIconItem> items();
    bool setItemAt(int index,const TrayIconItem &item);
    Q_INVOKABLE bool sendSignal(QString signalName,QString appName,int trayId);
    Q_INVOKABLE bool sendContextMenuSignal(int index,QString signalName,QString appName,int trayId);

    void setRunning(bool running);


signals:
    void preTrayIconRemoved(int index);
    void postTrayIconRemoved();
    void preTrayIconAppended();
    void postTrayIconAppended();
    void trayIconChanged(int index);
    void iconChanged(int index);



    //void preCustomTrayIconAppended();
    //void postCustomTrayIconAppended();

public slots:

    Q_SCRIPTABLE void showTrayIcon(QString appName,int trayId,QString imagePath,QString text,QStringList menus);
    Q_SCRIPTABLE void showCustomTrayIcon(QString appName,int trayId,QString qmlFilePath);//qmlFilePath is loaded with Loader
    Q_SCRIPTABLE int close(QString appName,int trayId);
    Q_SCRIPTABLE bool running();
    Q_SCRIPTABLE void changeIcon(QString appName,int trayId,QString imagePath);
private:
    QVector<TrayIconItem> trayIcons;
    QDBusConnection session = QDBusConnection::systemBus();
    bool m_running;

};

#endif // TRAYICONSERVER_H

/*
#ifndef TRAYICONSERVER_H
#define TRAYICONSERVER_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>

#include <QDBusObjectPath>
#include <QDebug>
#include "trayicon.h"
class TrayIconList : public QObject
{
    Q_OBJECT

public:
    TrayIconList();
    ~TrayIconList();
    QMap<QString,TrayIcon*> items();
    Q_INVOKABLE bool sendSignal(QString signalName,QString appName,int trayId);
    Q_INVOKABLE bool sendContextMenuSignal(int index,QString signalName,QString appName,int trayId);


    QString get(int index);
    int size();
    void connectSignals(TrayIcon* icon);
    void disconnectSignals(TrayIcon* icon);


signals:
    void preTrayIconRemoved(int index);
    void postTrayIconRemoved();
    void preTrayIconAppended();
    void postTrayIconAppended();
    void textChanged(int index);
    void imagePathChanged(int index);
    void trayIdChanged(int index);
    void menusChanged(int index);

public slots:
    void trayAdded(QString path);
    void trayRemoved(int index);
    void trayId(int index);
    void imagePath(int index);
    void text(int index);
    void menus(int index);


private:
    QMap<QString,TrayIcon*> trayIcons;
    QDBusConnection session = QDBusConnection::systemBus();

};

#endif // TRAYICONSERVER_H
*/

