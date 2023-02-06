#include "kfilemanager.h"
KFileManager::KFileManager()
{

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/", "com.kos.filemanager", "deleteFiles", this, SLOT(deleteFiles(QStringList)));
    session.connect("", "/", "com.kos.filemanager", "copyFile", this, SLOT(copyFile(QString,QStringList,QString)));
    session.connect("", "/", "com.kos.filemanager", "renameFile", this, SLOT(renameFile(QString, QString)));
    session.connect("", "/", "com.kos.filemanager", "moveFiles", this, SLOT(moveFiles(QString,QStringList,QString)));
    session.connect("", "/", "com.kos.filemanager", "getProgress", this, SLOT(getProgress()));
    session.connect("", "/", "com.kos.filemanager", "getMaxProgress", this, SLOT(getMaxProgress()));
    session.connect("", "/", "com.kos.filemanager", "cancel", this, SLOT(cancel()));
    session.connect("", "/", "com.kos.filemanager", "running", this, SLOT(running()));



    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObjects.");
        return;
    }

    if(!session.registerService("com.kos.filemanager")) {
        qFatal("Cannot registerObject2.");
        return;
    }


}

void KFileManager::sendDBusSignal(QString signal, QVariant var)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.filemanager", signal);
    QList<QVariant> list;
    list.append(var);

    m.setArguments(list);
    session.send(m);
}

void KFileManager::sendDBusSignal(QString signal)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.filemanager", signal);
    session.send(m);
}

void KFileManager::setMax(int max)
{
    if(max == 0 ){ setRunning(false);return;}
    m_maxProgress =max;
    sendDBusSignal("maxChanged",m_maxProgress);
    setRunning(true);

}

void KFileManager::setProgress(int progress)
{
    m_progress =progress;
    sendDBusSignal("progressChanged",m_progress);
}

void KFileManager::setRunning(bool running)
{
    if(m_running != running){
        m_running = running;
        sendDBusSignal("runningChanged",m_running);
    }
}

void KFileManager::copyPath(QString source, QString destination)
{

    if(!m_running) return;
    QDir dir(source);

    foreach(QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        QString dst_path =destination+QDir::separator()+d;
        dir.mkdir(dst_path);
        copyPath(source+QDir::separator()+d,dst_path);
        if(!m_running) break;
    }
    foreach(QString f, dir.entryList(QDir::Files)){

        if(!m_running) break;
        QFile file;
        QString newPath = destination+QDir::separator()+f;
        if(file.copy(source+QDir::separator()+f,destination+QDir::separator()+f)){
            updateFileCache(newPath,NULL,"add");
        }
    }

}

void KFileManager::updateFileCache(const QString &path,const QString &newPath,const QString& method)
{
    QFileInfo fInfo (path);
    if(fInfo.isDir()){
        QString folder = method+"Folder";
        callDBusMethod("/Audio",folder,path,newPath);
        callDBusMethod("/Video",folder,path,newPath);
        callDBusMethod("/Image",folder,path,newPath);
    }else{
        QMimeType type =db.mimeTypeForFile(path);
        if(type.name().contains("audio")){
            callDBusMethod("/Audio",method,path,newPath);

        }else if(type.name().contains("image")){
            callDBusMethod("/Image",method,path,newPath);

        }else if(type.name().contains("video")){
            callDBusMethod("/Video",method,path,newPath);

        }
    }
}

void KFileManager::callDBusMethod(const QString& type,const QString& method, const QString& path,const QString& newPath)
{


    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filecache",type,"",method);
    QVariantList list;
    list<<path;
    if(newPath != NULL){list<<newPath;}
    m.setArguments(list);
    QDBusConnection::systemBus().asyncCall(m);
}



void KFileManager::deleteFiles(QStringList filePaths)
{
    setMax(filePaths.size());
    for(int i=0;i<filePaths.size();i++){
        setProgress(i+1);
        QFileInfo fInfo (filePaths.at(i));
        updateFileCache(filePaths.at(i),NULL,"remove");

        if(fInfo.isDir()){

            QDir dir(filePaths.at(i));
            dir.removeRecursively();

        }else{
            QFile file (filePaths.at(i));
            file.remove();
        }
    }
    setMax(0);

    sendDBusSignal("deleteFinished");

}

void KFileManager::copyFile(QString path, QStringList fileNames, QString destination)
{


    setMax(fileNames.size());
    for(int i=0;i<fileNames.size();i++){
        if(!m_running)break;
        QString oldPath = path+QDir::separator()+fileNames.at(i);
        QString newPath = destination+QDir::separator()+fileNames.at(i);
        QFileInfo fileInfo(oldPath);
        setProgress(i+1);
        if(fileInfo.isDir()){
            QDir dir;
            if(dir.mkdir(newPath)){
                copyPath(oldPath,newPath);
            }


        }else{
            QFile file;
            if(file.copy(oldPath,newPath)){
                updateFileCache(newPath,NULL,"add");
            }
        }

    }

    setMax(0);

}

void KFileManager::renameFile(QString filePath, QString newName)
{
    if(m_running) return;

    QFile file(filePath);
    if(file.rename(newName)){
        updateFileCache(filePath,newName,"rename");
    }
    sendDBusSignal("renameFinished");


}

void KFileManager::moveFiles(QString path, QStringList fileNames, QString destination)
{
    if(m_running) return;
    setMax(fileNames.size());
    for(int i=0;i<fileNames.size();i++){
        setProgress(i+1);
        QString oldPath = path+"/"+fileNames.at(i);
        QString newPath = destination +"/"+fileNames.at(i);
        if(QFile::rename(oldPath,newPath)){
            updateFileCache(oldPath,newPath,"rename");

        }
    }
    setMax(0);
    sendDBusSignal("moveFinished");
}

int KFileManager::getProgress()
{
    return m_progress;
}

int KFileManager::getMaxProgress()
{
    return m_maxProgress;
}

void KFileManager::cancel()
{
    setRunning(false);
}

bool KFileManager::running()
{
    return m_running;;
}


