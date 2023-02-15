#include "applicationthread.h"

ApplicationThread::ApplicationThread()
{
    this->moveToThread(&thread);
    thread.start();

}

ApplicationThread::~ApplicationThread()
{

    thread.quit();
    thread.wait();


}

void ApplicationThread::load(const QString &filter)
{

    if(m_appList == NULL) return;

    m_appList->clear();
    QDirIterator it(SYSTEM_APPLICATIONS, {"*.conf"}, QDir::NoFilter, QDirIterator::Subdirectories);
    emit beginReset();

    while (it.hasNext()) {
        QString filename = it.next();

        QSettings desktopFile(filename, QSettings::IniFormat);
        desktopFile.setIniCodec("UTF-8");
        desktopFile.beginGroup("App");
        QString config_name = QFileInfo(desktopFile.fileName()).fileName();


        if(!filter.isEmpty()){

            QString fn = desktopFile.value("category").toString();
            if(fn.isEmpty()) continue;


            if(!fn.contains(filter)) continue;


        }

        ApplicationItem item;
        item.icon = desktopFile.value("icon", "applications-all").toString();
        item.path = desktopFile.value("path").toString();

        QString appDefName=desktopFile.value("name").toString();


        desktopFile.endGroup();
        desktopFile.beginGroup("Translations");
        item.name = appDefName;//desktopFile.value(Language::getCurrentLanguage(),appDefName).toString();
        desktopFile.endGroup();
        m_appList->append(item);


    }
    emit endReset();

}

bool ApplicationThread::startApp(QString filePath)
{
    QFileInfo info(filePath);
    QString fileExtension = info.suffix();
    QSettings extendedDefaultApps(QSettings::NativeFormat,QSettings::UserScope,"KOS","ExtendedDefaultApps");
    if(extendedDefaultApps.childGroups().contains(fileExtension)){
        extendedDefaultApps.beginGroup(fileExtension);
        QString path = extendedDefaultApps.value("path","").toString();
        extendedDefaultApps.endGroup();

        if(!path.isEmpty()){
            QVariantList list;
            list<<"file://"+filePath;
            launcher.start(path,list);
            loadEnded(false);
            return false;
        }
    }

    QSettings defaultApps(QSettings::NativeFormat,QSettings::UserScope,"KOS","DefaultApps");
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(filePath);
    QString mimeTypeName = type.name();
    mimeTypeName[0] = mimeTypeName[0].toUpper();
    QString nameSplit = mimeTypeName.split("/").first();
    if(defaultApps.childGroups().contains(nameSplit)){
        defaultApps.beginGroup(nameSplit);
        QString path = defaultApps.value("path","").toString();
        defaultApps.endGroup();

        if(!path.isEmpty()){
            QVariantList list;
            list<<"file://"+filePath;
            launcher.start(path,list);
            loadEnded(false);
            return false;
        }

    }

    load(nameSplit);
    loadEnded(true);
    return true;








}

void ApplicationThread::setList(QVector<ApplicationItem> *appList)
{
    m_appList = appList;
}
