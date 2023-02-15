#include "applicationsthread.h"
#include <QtDebug>
applicationsthread::applicationsthread(QObject *parent)
    : QObject{parent}
{
//    this->moveToThread(&thread);
  //  thread.start(QThread::LowPriority);

}

applicationsthread::~applicationsthread()
{

   // if(thread.isRunning()){
     //   thread.quit();
      //  thread.wait();
   // }
}

void applicationsthread::reset(const QString &filter, const QString &filterCategory, const QString &language)//fix language
{

    emit runningChanged(true);
    emit beginReset();
    if(!appList.isEmpty()) appList.clear();

    bool isFiltered = !filter.isEmpty() && !filterCategory.isEmpty();

    QDirIterator it(SYSTEM_APPLICATIONS, {"*.conf"}, QDir::NoFilter, QDirIterator::Subdirectories);

    while (it.hasNext()) {

        QString filename = it.next();

        QSettings desktopFile(filename, QSettings::IniFormat);
        desktopFile.setIniCodec("UTF-8");
        desktopFile.beginGroup("App");
        QString config_name = QFileInfo(desktopFile.fileName()).fileName();



        if(isFiltered){

            QString fn = desktopFile.value(filterCategory).toString();
            if(fn.isEmpty()) continue;


            if(!fn.contains(filter)) continue;


        }

        ApplicationItem item;


        item.icon = desktopFile.value("icon", "applications-all").toString();
        item.confPath=config_name;
        item.appPath = desktopFile.value("path", "").toString();
        QString appDefName=desktopFile.value("name").toString();


        desktopFile.endGroup();
        desktopFile.beginGroup("Translations");
        item.name = desktopFile.value(language,appDefName).toString();
        desktopFile.endGroup();


        appList.append(item);


    }
    emit endReset();
    emit runningChanged(false);


}

QList<ApplicationItem> *applicationsthread::getAppList()
{
    return &appList;
}
