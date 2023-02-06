#ifndef CACHEITEM_H
#define CACHEITEM_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>
#include <QThread>
#include <QDebug>

class CacheItem :public QObject
{
    Q_OBJECT
public:
    CacheItem();
    ~CacheItem();
    void init(QString type,QStringList* items);
    void sendFileRemoved(int index,QString path);
    void sendFileAdded(QString path);
    void sendFileRenamed(int index,QString oldPath,QString newPath);

public slots:
    Q_SCRIPTABLE void remove(QString path);
    Q_SCRIPTABLE void add(QString path);
    Q_SCRIPTABLE void rename(QString path,QString newPath);
    Q_SCRIPTABLE QString get(int index);
    Q_SCRIPTABLE int size();

    Q_SCRIPTABLE void removeFolder(QString path);
    Q_SCRIPTABLE void renameFolder(QString path,QString newPath);

private:

    QStringList *m_items= NULL;
    QString m_type;
    QDBusConnection system = QDBusConnection::systemBus();
};

#endif // CACHEITEM_H
