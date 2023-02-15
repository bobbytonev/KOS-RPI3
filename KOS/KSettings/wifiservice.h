#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <QObject>
//#include <QtDBus/QDBusConnection>
//#include <QtDBus/QDBusMessage>
//#include <QtDBus/QDBusArgument>
#include <QtDBus>
class WifiService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(int strength READ strength WRITE setStrength NOTIFY strengthChanged)
    Q_PROPERTY(QString security READ security WRITE setSecurity NOTIFY securityChanged)
    Q_PROPERTY(QString wifiPath READ wifiPath WRITE setWifiPath NOTIFY wifiPathChanged)

public:
    WifiService();

    QString name();
    void setName(QString name);

    QString state();
    void setState(QString state);

    int strength();
    void setStrength(int strength);

    QString wifiPath();
    void setWifiPath(QString wifiPath);

    QString security();
    void setSecurity(QString security);

    Q_INVOKABLE void makeConnection();
    Q_INVOKABLE void remove();
    Q_INVOKABLE void disconnect();

signals:
    void stateChanged();
    void strengthChanged();
    void nameChanged();
    void wifiPathChanged();
    void securityChanged();
public slots:
    void PropertyChanged(QString name,QDBusVariant var);

private:
    QString m_name;
    QString m_state;
    QString m_wifiPath;
    QString m_security;
    int m_strength;

};

#endif // WIFISERVICE_H
