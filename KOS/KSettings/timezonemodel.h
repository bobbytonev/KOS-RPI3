#ifndef TIMEZONEMODEL_H
#define TIMEZONEMODEL_H

#include <QAbstractListModel>
#include <QFile>
#include <QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QDBusPendingCall>
class TimezoneModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TimezoneModel(QObject *parent = nullptr);

    enum {
       TimeZone

    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;



    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;


    void loadTimeZones();

    Q_INVOKABLE QStringList getList();
    Q_INVOKABLE void setTimeZone(QString timeZone);



private:
    QStringList timeZones;
    int size;
    int timeZoneCount;
    int buffer = 10;
};

#endif // TIMEZONEMODEL_H
