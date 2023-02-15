#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QThread>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QtDBus/QDBusConnection>
struct TrayIconItem2
{

    QString appName,imagePath,text="";
    int trayId;
    bool imageProvider = true;
    QStringList menus={};
    QString objectPath;

};
class TrayIcon :public QObject
{
    Q_OBJECT
    Q_PROPERTY(int trayId READ trayId NOTIFY trayIdChanged)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged)
    Q_PROPERTY(QStringList menus READ menus NOTIFY menusChanged)
    Q_PROPERTY(QString objectPath READ objectPath WRITE setObjectPath NOTIFY objectPathChanged)

public:
    void sendSignal(QString signal,QString object);
    void registerDBus();

    int trayId();
    QString imagePath();
    QString text();
    QStringList menus();

    void setObjectPath(QString objectPath);
    QString objectPath();

    void getProperties();

    QVariant callMethod(QString method);

    void setIndex(int index);
    int index();

signals:
    void trayIdChanged(int index);
    void textChanged(int index);
    void imagePathChanged(int index);
    void menusChanged(int index);
    void objectPathChanged(int index);

public slots:
    void setTrayId(int trayId);
    void setText(QString text);
    void setMenus(QStringList menus);
    void setImagePath(QString imagePath);


public:
    TrayIcon();
private:
    int m_index = -1;
    QThread thread;
    TrayIconItem2 item;
    QDBusConnection session = QDBusConnection::systemBus();



};

#endif // TRAYICON_H
