#include "mimetypes.h"
#include "qdebug.h"

mimetypes::mimetypes()

{
    connect(this,&mimetypes::requestMimetype,this,&mimetypes::getMimeType);

}

bool mimetypes::running()
{
    return m_running;
}

void mimetypes::setRunning(bool running)
{
    if(m_running!=running){
        m_running = running;
        emit runningChanged();
    }
}


QStringList mimetypes::getMimetype(QString suffix)
{
    //setRunning(true);
    QString suffixFile = "test."+suffix;
    QList<QMimeType> list =  database.mimeTypesForFileName(suffixFile);
    if(list.isEmpty()) return {};
    QStringList mimeList {list.at(0).preferredSuffix(),list.at(0).name()};

    //setRunning(false);


    return mimeList;
}

void mimetypes::getMimeType(QString suffix)
{
    QString suffixFile = "test."+suffix;
    QList<QMimeType> list =  database.mimeTypesForFileName(suffixFile);
    if(list.isEmpty()) return;
    QStringList mimeList {list.at(0).preferredSuffix(),list.at(0).name()};
    emit mimetypeChanged(mimeList);


}

