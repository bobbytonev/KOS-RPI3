#ifndef USBMODEL_H
#define USBMODEL_H

#include <QAbstractListModel>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDebug>


class UsbModel : public QAbstractListModel
{
    Q_OBJECT

    struct UsbItem{
        QString moutingPoint,deviceName;
    };

public:

    enum {
        moutingPoint = Qt::UserRole,
        deviceName
    };
    explicit UsbModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;



    void activate();
    QStringList get(int index);
    int size();

public slots:
    void partitionInserted(QStringList usb);
    void partitionRemoved(QStringList usb);

private:
    QList<UsbItem> usbList;
};

#endif // USBMODEL_H
