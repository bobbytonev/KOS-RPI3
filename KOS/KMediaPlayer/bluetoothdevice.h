#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QObject>
#include <QtDBus/QtDBus>

class BluetoothDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged);
    Q_PROPERTY(QString devicePath READ devicePath WRITE setDevicePath NOTIFY devicePathChanged)
public:
    BluetoothDevice();

    void setStatus(QString status);
    QString status();

    void setTitle(QString title);
    QString title();

    void setDevicePath(QString objectPath);
    QString devicePath();

    void setProperties();
    void registerListener();

    QString getTitle(QVariant var);
signals:
    void statusChanged();
    void titleChanged();
    void devicePathChanged();
public slots:
    void PropertyChanged(QString interface_name, QVariantMap changed_properties,
                         QStringList invalidated_properties);
private:
    QString m_status;
    QString m_title;
    QString m_objectPath;


};

#endif // BLUETOOTHDEVICE_H
