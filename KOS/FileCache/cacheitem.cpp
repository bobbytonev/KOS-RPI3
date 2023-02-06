#include "cacheitem.h"



CacheItem::CacheItem()
{

}

CacheItem::~CacheItem()
{

}
void CacheItem::init(QString type, QStringList *items)
{
    m_type = type;
    if(m_items == NULL) m_items =items;

    //init D-Bus interface
    if (!system.isConnected())
    {
        qFatal("Cannot connect to the D-Bus system bus.");
        return;
    }


    system.connect("", m_type, "com.kos.filecache", "remove", this, SLOT(remove(QString)));
    system.connect("", m_type, "com.kos.filecache", "add", this, SLOT(add(QString)));
    system.connect("", m_type, "com.kos.filecache", "rename", this, SLOT(rename(QString,QString)));
    system.connect("", m_type, "com.kos.filecache", "removeFolder", this, SLOT(removeFolder(QString)));
    system.connect("", m_type, "com.kos.filecache", "renameFolder", this, SLOT(renameFolder(QString,QString)));
    system.connect("", m_type, "com.kos.filecache", "get", this, SLOT(get(int)));
    system.connect("", m_type, "com.kos.filecache", "size", this, SLOT(size()));



    if(!system.registerObject(m_type, this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObjects.");
        return;
    }

    if(!system.registerService("com.kos.filecache")) {
        qFatal("Cannot registerObject2.");
        return;
    }



}
void CacheItem::sendFileRemoved(int index, QString path)
{

    QDBusMessage m =QDBusMessage::createSignal(m_type,"com.kos.filecache", "fileRemoved");
    QList<QVariant> list;
    list.append(index);
    list.append(path);
    m.setArguments(list);
    system.send(m);
}

void CacheItem::sendFileAdded(QString path)
{

    QDBusMessage m =QDBusMessage::createSignal(m_type,"com.kos.filecache", "fileAdded");
    QList<QVariant> list;
    list.append(path);
    m.setArguments(list);
    system.send(m);

}

void CacheItem::sendFileRenamed(int index, QString oldPath, QString newPath)
{
    QDBusMessage m =QDBusMessage::createSignal(m_type,"com.kos.filecache", "fileRenamed");
    QList<QVariant> list;
    list.append(index);
    list.append(oldPath);
    list.append(newPath);
    m.setArguments(list);
    system.send(m);
}



void CacheItem::remove(QString path)
{
    qDebug()<<"REMOVE...";
    int index=-1;
    for(int i=0;i<m_items->size();i++){
        if(path.compare(m_items->at(i)) == 0){
            index = i;
            break;
        }
    }

    if(index >=0){
        m_items->removeAt(index);
        sendFileRemoved(index,path);

    }


}

void CacheItem::add(QString path)
{
    if(path.isEmpty()) return;


    m_items->append(path);
    sendFileAdded(path);


}

void CacheItem::rename(QString path, QString newPath)
{
qDebug()<<"RENAMING";
    int index =-1;
    for(int i=0;i<m_items->size();i++){
        if(m_items->at(i) == path){
            m_items->replace(i,newPath);
            index =i;
            break;
        }

    }
    qDebug()<<"INDEX:"<<index;
    if(index!=-1){
        sendFileRenamed(index,path,newPath);
    }

}

QString CacheItem::get(int index)
{
    if(index < 0) return "";


    return index < m_items->size() ? m_items->at(index) :"";



}

int CacheItem::size()
{

    return m_items->size();
}

void CacheItem::removeFolder(QString path)
{
    for(int i=0;i<m_items->size();i++){
        if(m_items->at(i).startsWith(path)){
            m_items->removeAt(i);
        }
    }
}

void CacheItem::renameFolder(QString path, QString newPath)
{
    for(int i=0;i<m_items->size();i++){
        if(m_items->at(i).startsWith(path)){
            QString nPath = m_items->at(i);
            m_items->replace(i,nPath.replace(path,newPath));
        }
    }
}

