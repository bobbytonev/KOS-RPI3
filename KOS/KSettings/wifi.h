#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QDebug>
class Wifi : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface","net.connman.Agent")
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
public:
    Wifi();
    ~Wifi();

    bool powered();
    void setPowered(bool powered);



    void getPowered();

    QString password();
    void setPassword(QString password);

    void registerAgent();
    void unregisterAgent();

    Q_INVOKABLE void sendPassword();
signals:
    void poweredChanged();
    void passwordChanged();
    void cancel();
    void error(QString error);
    void inputRequest();
public slots:
    Q_SCRIPTABLE QVariantMap RequestInput(QDBusObjectPath service,QVariantMap fields,const QDBusMessage& message);
    Q_SCRIPTABLE void Cancel();
    Q_SCRIPTABLE void ReportError(QDBusObjectPath service,QString errorName);
    Q_SCRIPTABLE void Release();
    void PropertyChanged(QString name, QDBusVariant var);


private:
    bool m_powered;
    bool firstRun = true;

    QString m_password;
    const QString OBJECT_PATH= "/kos/settings/wifiagent";
    QDBusMessage replyMessage;
};

#endif // WIFI_H
