#ifndef KFILEMANAGER_H
#define KFILEMANAGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDirIterator>
#include <QMimeType>
#include <QMimeDatabase>
#include <QDebug>

class KFileManager : public QObject
{
    Q_OBJECT
public:
    KFileManager();
    void sendDBusSignal(QString signal,QVariant var);
    void sendDBusSignal(QString signal);
    void setMax(int max);
    void setProgress(int progress);
    void setRunning(bool running);
    void copyPath(QString source,QString destination);

    void callDBusMethod(const QString& type,const QString& method, const QString& path,const QString& newPath);
    void updateFileCache(const QString& path, const QString& method, const QString& newPath);
public slots:
    Q_SCRIPTABLE void deleteFiles(QStringList filePaths);
    Q_SCRIPTABLE void copyFile(QString path,QStringList fileNames,QString destination);
    Q_SCRIPTABLE void renameFile(QString filePath, QString newName);
    Q_SCRIPTABLE void moveFiles(QString path,QStringList fileNames,QString destination);
    Q_SCRIPTABLE int getProgress();
    Q_SCRIPTABLE int getMaxProgress();
    Q_SCRIPTABLE void cancel();
    Q_SCRIPTABLE bool running();



private:
    bool m_running=false;
    int m_progress=0;
    int m_maxProgress=0;
    QMimeDatabase db;
    QDBusConnection session = QDBusConnection::sessionBus();



};

#endif // KFILEMANAGER_H
