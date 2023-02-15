#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QObject>
#include <QtDBus/QtDBus>

class BluetoothDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool paired READ paired NOTIFY pairedChanged);
    Q_PROPERTY(bool trusted READ trusted NOTIFY trustedChanged);
    Q_PROPERTY(QString name READ name NOTIFY nameChanged);
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged);
    Q_PROPERTY(QString adress READ adress NOTIFY adressChanged);
    Q_PROPERTY(QString devicePath READ devicePath WRITE setDevicePath NOTIFY devicePathChanged)
public:
    BluetoothDevice();



    const QString &devicePath() const;
    void setDevicePath(const QString &newDevicePath);


    const QString &adress() const;

    const QString &icon() const;
    const QString &name() const;
    bool trusted() const;

    void setPaired(bool paired);
    bool paired() const;

    void setConnected(bool connected);
    bool connected() const;

    void getProperties();
    void registerListener();

    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void makeConnection();
    Q_INVOKABLE void removeDevice();

public slots:
    void PropertyChanged(QString interface_name, QVariantMap changed_properties,
                         QStringList invalidated_properties);
signals:
    void devicePathChanged();
    void adressChanged();
    void iconChanged();
    void nameChanged();
    void trustedChanged();
    void pairedChanged();
    void connectedChanged();

private:
    bool m_connected;
    bool m_paired;
    QString m_adress;
    QString m_devicePath;
    QString m_icon;
    QString m_name;
    bool m_trusted;
};

#endif // BLUETOOTHDEVICE_H
