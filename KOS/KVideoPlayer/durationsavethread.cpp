#include "durationsavethread.h"

DurationSaveThread::DurationSaveThread()
{
    //connect(&timer,&QTimer::timeout,this,save)
    this->moveToThread(&thread);

}
DurationSaveThread::~DurationSaveThread()
{
    stopThread();
}

void DurationSaveThread::saveProgress(int progress)
{
    QFile file(m_source);



    if(isSaved){

        qDebug()<<"SAVED";
        file.resize(file.size()-sizeof(int));
    }
    if(file.open(QIODevice::Append)){

        qDebug()<<progress;
        qDebug()<<file.write(reinterpret_cast<char *>(&progress),sizeof(int));
    }
    file.close();
    isSaved = true;
}

void DurationSaveThread::stopThread()
{
    if(thread.isRunning()){
        thread.quit();
        thread.wait();
    }
}

void DurationSaveThread::startThread()
{
    if(!thread.isRunning()) thread.start();
}

void DurationSaveThread::getProgress(QString source)
{

    source = source.replace("file://","");
    isSaved=false;
    QFile file(source);
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<"HERE";
        file.seek(file.size()-sizeof(int));
        int data;
        file.read(reinterpret_cast<char *>(&data),sizeof(int));
        qDebug()<<data;
        if(data>=0 && data<101){
            isSaved =true;
            emit progressChanged(data);

        }
        m_source = source;

    }
    file.close();



}
