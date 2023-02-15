#include "defaultapplicationsthread.h"

DefaultApplicationsThread::DefaultApplicationsThread()
{
    this->moveToThread(this);
    this->start(QThread::LowPriority);
}

DefaultApplicationsThread::~DefaultApplicationsThread()
{
    if(this->isRunning()){
        this->quit();
        this->wait();
    }
}

QString DefaultApplicationsThread::getAppName(QString config)//fix language
{
    if(config.isEmpty()) return "";

    QString USER_APPLICATIONS = "/usr/share/applications/";

    QSettings settings(USER_APPLICATIONS+config,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    settings.beginGroup("App");
    QString appName =settings.value("name").toString();
    settings.endGroup();

    settings.beginGroup("Translations");
    QString translateAppName =settings.value(language,appName).toString();

    settings.endGroup();

    return translateAppName;

}

QList<DefaultApps> *DefaultApplicationsThread::getDefaultAppList()
{
    return &defaultApps;
}

void DefaultApplicationsThread::setLanguage(const QString &lang)
{
    language =lang;
}

void DefaultApplicationsThread::reset(bool extended)
{
    emit beginReset();
    emit running(true);

    m_extended = extended;
    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS", extended ?"ExtendedDefaultApps":"DefaultApps");
    settings.setIniCodec("UTF-8");
    QStringList groups =settings.childGroups();

    for(int i=0;i<groups.size();i++){


        settings.beginGroup(groups.at(i));

        DefaultApps item ;
        item.path=settings.value("path").toString();
        item.icon=settings.value("icon").toString();
        item.config=settings.value("config","").toString();

        //if(extended)
            item.category=groups.at(i);
        //else
          //  item.category=settings.value(language,groups.at(i)).toString();

        item.name=getAppName(item.config);


        if(extended) item.mimetypeName=settings.value("mimetype").toString();


        settings.endGroup();
        defaultApps.append(item);
    }


    emit running(false);
    emit endReset();
}

void DefaultApplicationsThread::changeData(int index, QString appConfig, QString path, QString icon)
{
    if(index < 0 ||index >= defaultApps.size()) return;

    DefaultApps app = defaultApps.at(index);
    app.name = getAppName(appConfig);
    app.path = path;
    app.icon = icon;
    app.config=appConfig;

    defaultApps[index]=app;
    emit dataChanged(index);
    saveToSettings(index);
}

void DefaultApplicationsThread::removeItem(int index)
{
    QString group = defaultApps.at(index).category;
    emit preItemRemoved(index);
    defaultApps.removeAt(index);
    emit postItemRemoved();
    removeFromSettings(group);
}

void DefaultApplicationsThread::saveToSettings(int index)
{
    const DefaultApps& app = defaultApps.at(index);
    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS", m_extended ?"ExtendedDefaultApps":"DefaultApps");
    settings.beginGroup(app.category);
    settings.setValue("name",app.name);
    settings.setValue("path",app.path);
    settings.setValue("icon",app.icon);
    settings.setValue("config",app.config);

    settings.endGroup();


}

void DefaultApplicationsThread::addItem(QString group,QString mimetype)
{
    emit preItemAdded(defaultApps.size());
    DefaultApps app;
    app.category = group;
    app.mimetypeName = mimetype;
    defaultApps.append(app);
    emit postItemAdded();


    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS","ExtendedDefaultApps");
    settings.beginGroup(group);
    settings.setValue("mimetype",mimetype);
    settings.endGroup();

}

void DefaultApplicationsThread::removeFromSettings(QString group)
{

    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS","ExtendedDefaultApps");
    settings.beginGroup(group);
    settings.remove("");
    settings.endGroup();

}
