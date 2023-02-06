#include "kfilemanager.h"
#include <QDebug>
#include <QDir>
KFileManager::KFileManager()
{

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SessionBus,"com.kos.filemanager");
    conn.connect("", "/", "com.kos.filemanager","copyFinished",this,SIGNAL(copyFinished()));
    conn.connect("", "/", "com.kos.filemanager","moveFinished",this,SIGNAL(moveFinished()));
    conn.connect("", "/", "com.kos.filemanager","renameFinished",this,SIGNAL(renameFinished()));
    conn.connect("", "/", "com.kos.filemanager","deleteFinished",this,SIGNAL(deleteFinished()));

    conn.connect("", "/", "com.kos.filemanager","progressChanged",this,SLOT(setProgress(int)));
    conn.connect("", "/", "com.kos.filemanager","maxChanged",this,SLOT(setMat(int)));
    conn.connect("", "/", "com.kos.filemanager","runningChanged",this,SLOT(setRunning(bool)));
    m_max = setProperties("getMaxProgress").toInt();
    m_progress = setProperties("getProgress").toInt();
    m_running = setProperties("running").toBool();



}
void KFileManager::createFolder(QString path){
    QDir dir(path);
    if(!dir.exists()){
       dir.mkpath(path);
    }

}

void KFileManager::sendDbusMethod(QString methodName, const QVariantList &list)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filemanager", "/","",methodName);
    m.setArguments(list);
    QDBusConnection::sessionBus().asyncCall(m);

}

void KFileManager::copy(QString path, QStringList fileNames, QString destination){
    QVariantList list;
    list<<path<<fileNames<<destination;
    sendDbusMethod("copyFile",list);
}
void KFileManager::remove(QStringList files){
    QVariantList list;
    list<<files;
    sendDbusMethod("deleteFiles",list);
}
void KFileManager::move(QString path, QStringList fileNames, QString destination){
    QVariantList list;
    list<<path<<fileNames<<destination;
    sendDbusMethod("moveFiles",list);
}
void KFileManager::rename(QString filePath, QString newName){
    QVariantList list;
    list<<filePath<<newName;
    sendDbusMethod("renameFile",list);
}
int KFileManager::max()
{
    return m_max;
}

int KFileManager::progress()
{
    return m_progress;
}
void KFileManager::setProgress(int progress){

    if(m_progress != progress){
        m_progress = progress;
        emit progressChanged();
    }
}
void KFileManager::setMax(int max){
    if(m_max != max){
        m_max = max;
        emit maxChanged();
    }
}
void KFileManager::setRunning(bool running){
    if(m_running != running){
        m_running = running;
        emit runningChanged();
    }
}
bool KFileManager::running(){
    return m_running;
}

QVariant KFileManager::setProperties(QString method)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filemanager","/", "", method);
    QDBusMessage reply =QDBusConnection::sessionBus().call(m);
    QVariantList list = reply.arguments();
    return list.first();
}
