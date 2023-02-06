#include "styles.h"

Styles::Styles()
{



    QSettings::setPath(QSettings::NativeFormat,QSettings::SystemScope,"/etc/");

    loadFromSettings();

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/", "com.kos.stylemanager", "iconPackName", this, SLOT(iconPackName(void)));
    session.connect("", "/", "com.kos.stylemanager", "appStyleName", this, SLOT(appStyleName(void)));

    session.connect("", "/", "com.kos.stylemanager", "setIconPackName", this, SLOT(setIconPackName(QString)));
    session.connect("", "/", "com.kos.stylemanager", "setAppStyleName", this, SLOT(setAppStyleName(QString)));

    session.connect("", "/", "com.kos.stylemanager", "changeProperty", this, SLOT(changeProperty(void)));

    session.connect("", "/", "com.kos.stylemanager", "size", this, SLOT(size()));
    session.connect("", "/", "com.kos.stylemanager", "get", this, SLOT(get(int)));


    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.stylemanager")) {
        qFatal("Cannot registerService.");
        return;
    }
    loadConfig();

    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.environment");
    conn.connect("", "/TrayIcons", "com.kos.environment","runningChanged",this,SLOT(showTray()));
    conn.connect("", "/TrayIcons", "com.kos.environment","kosstylemanagerClicked2367",this,SLOT(clicked()));




}

bool Styles::saveToSettings(QString key, QString value, bool prop)
{
    if(!prop){
        QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"style-manager", "style");

        settings.beginGroup("Appearance");
        settings.setValue(key,value);
        settings.endGroup();
        settings.sync();
        return true;

    }else{
        QSettings settings(STYLES_FOLDER+m_styleName+"/Themes.conf",QSettings::IniFormat);


        settings.beginGroup(GROUP_NAME);

        //if(!settings.contains(key)) return false;

        settings.setValue(key,value);
        settings.endGroup();
        settings.sync();
        return true;

    }

}

void Styles::loadFromSettings()
{
    QSettings settings(QSettings::NativeFormat,QSettings::SystemScope,"style-manager", "style");

    settings.beginGroup("Appearance");

    m_iconPack = settings.value("IconPack","candy-icons").toString();
    m_styleName = settings.value("Style","Tranpy").toString();


    settings.endGroup();




}

void Styles::emitDbusSignal(QString signalName, QString message)
{
    QDBusMessage m =QDBusMessage::createSignal("/","com.kos.stylemanager", signalName);
    QList<QVariant> list;
    list.append(message);
    m.setArguments(list);
    session.send(m);
}

void Styles::loadConfig()
{
    if(!themeConfig.isEmpty()) themeConfig.clear();
    QSettings settings(STYLES_FOLDER+appStyleName()+"/Themes.conf",QSettings::IniFormat);
    settings.beginGroup(GROUP_NAME);

    //QStringList groups =settings.childGroups();
    QStringList childKeys =settings.childKeys();
    //for(int i=0;i<keys.size();i++){
    //settings.beginGroup(groups.at(i));
    //QStringList childKeys = settings.childKeys();
    foreach (const QString &childKey, childKeys){

        if(childKey.compare("Dark") == 0){
            hasDarkMode=true;
            darkMode=settings.value(childKey).toBool();
        }
        // themeConfig.insert(childKey,QVariant::fromValue(QVariantList{groups.at(i),settings.value(childKey)}));

        // QStringList list{childKey,groups.at(i),settings.value(childKey).toString()};
        QStringList list{childKey,settings.value(childKey).toString()};
        themeConfig.append(list);


    }
    settings.endGroup();

    //}
    if(hasDarkMode){
        icon.show("",darkMode ? "style-manager-dark":"style-manager-light");
    }else{
        icon.close();
    }


}

bool Styles::itemAt(QString key,QString value)
{

    for(int i=0;i<themeConfig.size();i++){
        QStringList oldList = themeConfig.at(i);
        if(oldList.at(0).compare(key) == 0){
            QStringList newList {key,value};
            themeConfig[i] = newList;
            return true;
        }
    }

    return false;
}

void Styles::switchMode()
{
    if(hasDarkMode){
        darkMode= !darkMode;
        // changeProperty("Dark","Switch",darkMode ? "true":"false");
        changeProperty("Dark",darkMode ? "true":"false");


    }

}

void Styles::setIconPackName(QString iconPack)
{
    if(m_iconPack != iconPack && !iconPack.isEmpty()){
        m_iconPack = iconPack;
        emitDbusSignal("iconPackChanged",iconPack);
        saveToSettings("IconPack",iconPack,false);

    }
}

QString Styles::iconPackName()
{

    return m_iconPack;
}

void Styles::setAppStyleName(QString styleName)
{
    if(m_styleName != styleName && !styleName.isEmpty()){
        m_styleName = styleName;
        hasDarkMode = false;
        loadConfig();
        emitDbusSignal("styleNameChanged",styleName);
        saveToSettings("Style",styleName,false);

    }
}

QString Styles::appStyleName()
{


    return m_styleName;
}

void Styles::changeProperty(QString key, QString value)
{
    if(itemAt(key,value)){
        QDBusMessage m =QDBusMessage::createSignal("/","com.kos.stylemanager", "propertyChanged");
        QList<QVariant> list;
        list.append(key);
        list.append(value);
        m.setArguments(list);
        session.send(m);
        saveToSettings(key,value,true);
    }


}

int Styles::size()
{
    return themeConfig.size();
}

QStringList Styles::get(int index)
{

    QStringList list{};
    return index < 0 || index >= themeConfig.size() ? list : themeConfig.at(index);
}

void Styles::showTray()
{
    if(hasDarkMode)
        icon.show("",darkMode ? "style-manager-dark":"style-manager-light");
}

void Styles::clicked()
{
    switchMode();
    icon.show("",darkMode ? "style-manager-dark":"style-manager-light");
}


