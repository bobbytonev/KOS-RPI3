#ifndef WIFIMODEL_H
#define WIFIMODEL_H

#include <QAbstractListModel>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>
class WifiModel : public QAbstractListModel
{
    Q_OBJECT

    struct WifiItem{
        QString name,state,security;
        int strength;

    };
    struct ServiceItem{
        QDBusObjectPath path;
        QVariantMap map;
    };
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)

public:
    enum {
        ServicePath = Qt::UserRole,
        ServiceState,ServiceName,ServiceStrength,ServiceSecurity

    };
    explicit WifiModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void activate(bool connectToSignal);
    Q_INVOKABLE void scan();

    QString state();
    void setState(QString state);

    bool setServiceArray(QList<ServiceItem>& list,const QDBusMessage& message);

    void createItem(QString objectPath, QVariantMap vars);


public slots:
    void returnMethod();
    void errorMethod();
    void ServicesChanged(QList<QVariant> vlist,QList<QDBusObjectPath> servicesRemoved,QDBusMessage message);

signals:
    void stateChanged();
private:
    QMap<QString,WifiItem> services;
    bool m_scanFinished=true;
    QString m_state = "";
    //QStringList services;
};

#endif // WIFIMODEL_H
