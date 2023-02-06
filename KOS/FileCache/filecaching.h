#ifndef FILECACHING_H
#define FILECACHING_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QMimeDatabase>
#include <QMimeType>
#include "cacheitem.h"
//add save to cache when shutdown or update cache where there is unenspeteced shutdown
class FileCaching :public QObject
{
    Q_OBJECT
    //0 - audio
    //1 - image
    //2 - video
public:
    FileCaching();
    ~FileCaching();

    void updateSystemFileCache(QString group, QStringList array);
    void getSystemFileCache(QString group, QStringList *array);
    void init();
    bool configGenerator();
    void initCacheItem(QThread *thread,CacheItem* item,QString type,QStringList* items);
    void stopThread(QThread *thread);

    QStringList getAudio();
    QStringList getVideo();
    QStringList getImage();

    /*
    void sendFileRemoved(int index,QString path,int type);
    void sendFileAdded(QString path,int type);
    void sendFileRenamed(int index,QString oldPath,QString newPath,int type);
    bool configGenerator();

*/


public slots:
    /*
    Q_SCRIPTABLE void remove(QString path,int type);
    Q_SCRIPTABLE void add(QString path,int type);
    Q_SCRIPTABLE void rename(QString path,QString newPath,int type);
    Q_SCRIPTABLE QString get(int index,int type);
    Q_SCRIPTABLE int size(int type);
    */
    void updateSettings();
    Q_SCRIPTABLE void shutdown();
    Q_SCRIPTABLE void reboot();




private:
    QStringList audio;
    QStringList video ;
    QStringList image ;
    QMimeDatabase db;

    CacheItem audio_item;
    CacheItem video_item;
    CacheItem image_item;

    QThread audio_thread;
    QThread video_thread;
    QThread image_thread;


    const QString CONFIG_NAME = "FileCache";



};

#endif // FILECACHING_H
