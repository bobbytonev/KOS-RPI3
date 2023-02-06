#include "appinfo.h"
#include <QDebug>
AppInfo::AppInfo(QObject *parent)
    : QObject{parent}
{

}

void AppInfo::setName(const QString &name)
{
    if(m_name != name){
        m_name= name;
        emit nameChanged();
    }
}

QString AppInfo::name()
{
    return m_name;
}
void AppInfo::setIcon(const QString &icon)
{
    if(m_icon != icon){
        m_icon= icon;
        emit iconChanged();
    }
}

QString AppInfo::icon()
{
    return m_icon;
}
void AppInfo::setConfigPath(const QString &configPath)
{

    QSettings settings("/usr/share/applications/"+configPath,QSettings::IniFormat);
    m_configPath = configPath;


    settings.setIniCodec("UTF-8");
    settings.beginGroup("App");

    setIcon(settings.value("icon", "applications-all").toString());
    QStringList info;
    info<<(settings.value("path","Application").toString());
    info<<settings.value("category","Application").toString();
    info<<settings.value("version","1.0").toString();
    setInfo(info);



    QString appDefName=settings.value("name").toString();
    settings.endGroup();
    settings.beginGroup("Translations");
    setName(appDefName);//settings.value(Language::getCurrentLanguage(),appDefName).toString();
    settings.endGroup();
}

QString AppInfo::configPath()
{
    return m_configPath;
}

void AppInfo::setInfo(const QStringList &info)
{

    if(m_info != info){
        m_info= info;
        emit infoChanged();
    }
}

QStringList AppInfo::info()
{
    return m_info;
}
