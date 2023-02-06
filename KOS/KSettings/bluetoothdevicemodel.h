#ifndef BLUETOOTHDEVICEMODEL_H
#define BLUETOOTHDEVICEMODEL_H

#include <QAbstractListModel>
#include <QtDBus/QtDBus>
class BluetoothDeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        DevicePath = Qt::UserRole,

    };
    explicit BluetoothDeviceModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void activate();
public slots:
    void InterfacesRemoved(QDBusObjectPath path,QStringList list);
    void InterfacesAdded(QDBusObjectPath path,QVariantMap list);

private:
    QStringList btDevices;
};

#endif // BLUETOOTHDEVICEMODEL_H
