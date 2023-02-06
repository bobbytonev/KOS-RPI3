#include "timezonemodel.h"

#include <QTextStream>

TimezoneModel::TimezoneModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadTimeZones();
}

int TimezoneModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return size;
}
QHash<int, QByteArray> TimezoneModel::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[TimeZone] = "timeZone";


    return roles;
}



bool TimezoneModel::canFetchMore(const QModelIndex &parent) const
{
    if(parent.isValid())
        return false;
    return timeZoneCount < size;

}

void TimezoneModel::fetchMore(const QModelIndex &parent)
{
    if(parent.isValid())
        return;

    const int start = timeZoneCount;
    const int reminder = size - start;
    const int itemToFetch = qMin(buffer,reminder);

    if(itemToFetch <=0)
        return;

    beginInsertColumns(QModelIndex(),start,start+itemToFetch-1);
    timeZoneCount+=itemToFetch;
    endInsertRows();

}

QVariant TimezoneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    if(row >= size || row <0)
        return {};


    switch (role) {
    case TimeZone:
        return timeZones.at(row);

    default:
        return QVariant();

    }
    return QVariant();
}

void TimezoneModel::loadTimeZones()
{
    QFile file("/usr/share/zoneinfo/zone.tab");
    if(!file.open(QIODevice::ReadOnly)){

        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line =in.readLine();

        if(!line.startsWith("#")){

            QStringList str =line.split('\t');
            if(str.size()>2){
                timeZones.append(str.at(2));
            }
        }
    }

    file.close();
    size = timeZones.size();
}

QStringList TimezoneModel::getList()
{
    return timeZones;
}

void TimezoneModel::setTimeZone(QString timeZone)
{
    QDBusMessage m =QDBusMessage::createMethodCall("com.kos.clockmanager","/","", "changeTimeZone");
    QList<QVariant> list;
    list.append(timeZone);
    m.setArguments(list);
    QDBusConnection::systemBus().asyncCall(m);

}
