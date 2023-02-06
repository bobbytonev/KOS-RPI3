#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <QObject>
#include <QDebug>
#include <QtDBus/QtDBus>
class BluetoothManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
public:
    BluetoothManager();

    bool powered();
    void setPowered(bool powered);

    QString name();
    void setName(QString name);

    bool enabled();
    void setEnabled(bool enabled);

    void init();

    Q_INVOKABLE   void setProperty(QString method,QVariant var,bool errorSlot);


signals:
    void enabledChanged();
    void poweredChanged();
    void nameChanged();
public slots:
    void PropertyChanged(QString interface_name, QVariantMap changed_properties,
                         QStringList invalidated_properties);
    void error();
    void returnMethod();



private:
    bool m_powered;
    bool m_enabled=true;
    QString m_name;

};

#endif // BLUETOOTHMANAGER_H
