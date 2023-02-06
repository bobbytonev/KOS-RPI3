#ifndef BLUETOOTHDEVICEMODEL_H
#define BLUETOOTHDEVICEMODEL_H

#include <QAbstractListModel>
#include <QtDBus/QtDBus>
class BluetoothDeviceModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit BluetoothDeviceModel(QObject *parent = nullptr);

    enum {
        ObjectPath = Qt::UserRole,
        Icon,Name,Status,Title

    };


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void activate();
    QString getIcon(QString objectPath) const;
    QString getName(QString objectPath) const;
    QString get(int index) const;
    int size() const;

    Q_INVOKABLE void sendCommand(QString command,QString objectPath);


public slots:
    void deviceAdded(QString path);
    void deviceRemoved(int index);

private:

};

#endif // BLUETOOTHDEVICEMODEL_H
