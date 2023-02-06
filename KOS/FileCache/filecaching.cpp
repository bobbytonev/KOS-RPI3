#include "filecaching.h"

FileCaching::FileCaching()
{



    QSettings::setPath(QSettings::NativeFormat,QSettings::SystemScope,"/etc/");


    init();

}

FileCaching::~FileCaching()
{

    stopThread(&audio_thread);
    stopThread(&video_thread);
    stopThread(&image_thread);
}

void FileCaching::updateSystemFileCache(QString group,QStringList array)
{



    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"file-cache", CONFIG_NAME);
    settings.remove(group);
    settings.beginGroup(group);
    settings.beginWriteArray(group.toLower());
    for(int i=0;i<array.size();i++){
        settings.setArrayIndex(i);
        settings.setValue("path",array.at(i));
    }

    settings.endArray();
    settings.endGroup();
    settings.sync();

}
void FileCaching::getSystemFileCache(QString group, QStringList *array)
{


    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"file-cache", CONFIG_NAME);
    settings.beginGroup(group);
    int size =settings.beginReadArray(group.toLower());
    for(int i=0;i<size;i++){

        settings.setArrayIndex(i);
        array->append(settings.value("path").toString());
    }

    settings.endArray();
    settings.endGroup();

}

bool FileCaching::configGenerator()
{

    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"file-cache", CONFIG_NAME);
    bool uClose = settings.value("UnexpectedClose","true").toBool();
    qDebug()<<uClose;

    if(uClose){
        audio.clear();video.clear();image.clear();
        QDir selectedDir(QDir::homePath()+"/str");


        selectedDir.setFilter(QDir::Files|QDir::Dirs | QDir::NoDot | QDir::NoDotDot );
        QDirIterator it(selectedDir,QDirIterator::Subdirectories);

        while(it.hasNext()){
            QString dirName =it.next();


            QMimeType type =db.mimeTypeForFile(dirName);
            if(type.name().contains("audio")){
                audio.append(dirName);
            }else if(type.name().contains("image")){
                image.append(dirName);
            }else if(type.name().contains("video")){

                video.append(dirName);
            }
        }
        updateSystemFileCache("Audio",audio);
        updateSystemFileCache("Image",image);
        updateSystemFileCache("Video",video);

        return true;
    }else{
        settings.setValue("UnexpectedClose","true");
    }

    return false;

}

void FileCaching::initCacheItem(QThread *thread,CacheItem* item,QString type,QStringList* items)
{

    item->init(type,items);
    item->moveToThread(thread);
    thread->start();

}

void FileCaching::stopThread(QThread *thread)
{
 if(thread->isRunning()){
     thread->quit();
     thread->wait();
 }
}
QStringList FileCaching::getAudio()
{
    return audio;
}
QStringList FileCaching::getImage()
{
    return image;
}
QStringList FileCaching::getVideo()
{
    return video;
}

void FileCaching::init()
{

    if(!configGenerator()){


        getSystemFileCache("Audio",&audio);
        getSystemFileCache("image",&image);
        getSystemFileCache("video",&video);
    }
    initCacheItem(&audio_thread,&audio_item,"/Audio",&audio);
    initCacheItem(&video_thread,&video_item,"/Video",&video);
    initCacheItem(&image_thread,&image_item,"/Image",&image);

    // audio_item->moveToThread(&thread);

    // item_audio.init2("/Audio",&audio);
    //item_video().init("/Video",&video);
    // item_image().init("/Image",&image);


    /*
            //init D-Bus interface
            if (!system.isConnected())
            {
                qFatal("Cannot connect to the D-Bus system bus.");
                return;
            }

            system.connect("", "/", "com.kos.filecache", "remove", this, SLOT(remove(QString,int)));
            system.connect("", "/", "com.kos.filecache", "add", this, SLOT(add(QString,int)));
            system.connect("", "/", "com.kos.filecache", "rename", this, SLOT(rename(QString,QString,int)));
            system.connect("", "/", "com.kos.filecache", "get", this, SLOT(get(int,int)));
            system.connect("", "/", "com.kos.filecache", "size", this, SLOT(size(int)));



            if(!system.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
                qFatal("Cannot registerObject.");
                return;
            }

            if(!system.registerService("com.kos.filecache")) {
                qFatal("Cannot registerObject.");
                return;
            }
        */


}
/*
void FileCaching::sendFileRemoved(int index, QString path, int type)
{

    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.filecache", "fileRemoved");
    QList<QVariant> list;
    list.append(index);
    list.append(path);
    list.append(type);
    m.setArguments(list);
    system.send(m);
}

void FileCaching::sendFileAdded(QString path, int type)
{

    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.filecache", "fileAdded");
    QList<QVariant> list;
    list.append(path);
    list.append(type);
    m.setArguments(list);
    system.send(m);

}

void FileCaching::sendFileRenamed(int index, QString oldPath, QString newPath, int type)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.filecache", "fileRenamed");
    QList<QVariant> list;
    list.append(index);
    list.append(oldPath);
    list.append(newPath);
    list.append(type);
    m.setArguments(list);
    system.send(m);
}


void FileCaching::remove(QString path, int type)
{
    if(type < 0 || type > 2) type = 2;

    QStringList *types = type  == 0 ? &audio : type ==1 ? &image : &video;
    int index=-1;
    for(int i=0;i<types->size();i++){
        if(path.compare(types->at(i)) == 0){
            index = i;
            break;
        }
    }

    if(index >=0){
        types->removeAt(index);
        sendFileRemoved(index,path,type);

    }


}

void FileCaching::add(QString path, int type)
{
    if(path.isEmpty()) return;

    bool error=false;

    switch (type) {
    case 0:
        audio.append(path);

        break;
    case 1:
        image.append(path);
        break;
    case 2:
        video.append(path);
        break;
    default:
        error=true;
        break;
    }

    if(!error)
        sendFileAdded(path,type);


}

void FileCaching::rename(QString path, QString newPath, int type)
{
    if(type < 0 || type > 2) type = 2;

    QStringList *types = type  == 0 ? &audio : type ==1 ? &image : &video;
    int index =-1;
    for(int i=0;i<types->size();i++){
        if(types->at(i).compare(path) == 0){
            types->replace(i,newPath);
            index =i;
            break;
        }

    }
    if(index!=-1){
        sendFileRenamed(index,path,newPath,type);
    }

}

QString FileCaching::get(int index, int type)
{
    if(index < 0) return "";


    switch (type) {
    case 0:
        return index < audio.size() ? audio.at(index) :"";
    case 1:
        return index < image.size() ? image.at(index) :"";
    case 2:
        return index < video.size() ? video.at(index) :"";
    default:
        return "";
    }

}

int FileCaching::size(int type)
{
    switch (type) {
    case 0:
        return audio.size();
    case 1:
        return image.size();
    case 2:
        return video.size();
    default:
        return -1;
    }
}
*/

void FileCaching::updateSettings()
{

    updateSystemFileCache("Audio",audio);
    updateSystemFileCache("Image",image);
    updateSystemFileCache("Video",video);
    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"file-cache", CONFIG_NAME);
    settings.setValue("UnexpectedClose","false");

}

void FileCaching::shutdown()
{
    updateSettings();
}

void FileCaching::reboot()
{
    updateSettings();
}
