#include "language.h"

Language::Language(QObject *parent)
    : QObject{parent}
{
    getLanguageFromSettings();

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/Language", "com.kos.stylemanager", "getLanguage", this, SLOT(getLanguage(void)));
    session.connect("", "/Language", "com.kos.stylemanager", "setLanguage", this, SLOT(setLanguage(QString)));

    session.connect("", "/Language", "com.kos.stylemanager", "languageAt", this, SLOT(languageAt(QStringList)));
    session.connect("", "/Language", "com.kos.stylemanager", "size", this, SLOT(size(int)));

    if(!session.registerObject("/Language", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.stylemanager")) {
        qFatal("Cannot registerService.");
        return;
    }


}

void Language::getLanguageFromSettings()
{

    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"style-manager", "Language");
    settings.setIniCodec("UTF-8");
    currentLanguage = settings.value("current","bg_Bg").toString();
    QStringList groups =settings.childGroups();

    for(int i=0;i<groups.size();i++){
        settings.beginGroup(groups.at(i));
        QStringList language {settings.value("name").toString(),groups.at(i)};
        languageList.append(language);
        settings.endGroup();
    }

}

void Language::languageChanged()
{
    QDBusMessage m =QDBusMessage::createSignal("/Language","com.kos.stylemanager", "languageChanged");
    QList<QVariant> list;
    list.append(currentLanguage);
    m.setArguments(list);
    session.send(m);
}

void Language::saveToSettings()
{
    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"style-manager", "Language");
    settings.setIniCodec("UTF-8");
    settings.setValue("current",currentLanguage);
    settings.sync();

}

QString Language::getLanguage()
{
    return currentLanguage;
}
void Language::setLanguage(QString language){

    if(currentLanguage != language){
        currentLanguage = language;
        languageChanged();
        saveToSettings();

    }

}

int Language::size()
{
    return languageList.size();
}

QStringList Language::languageAt(int index)
{
    if(index < 0 || index >= languageList.size())  return QStringList{};

    return languageList.at(index);
}
