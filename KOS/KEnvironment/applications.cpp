#include "applications.h"
//#include "language.h"
applications::applications(QObject *parent)
    : QAbstractListModel(parent)
{
}

int applications::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return appList.size();
}

QVariant applications::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ApplicationItem item = appList.at(index.row());
    switch (role) {
    case Name:
        return QVariant(item.name).toString();
    case Icon:
        return QVariant(item.icon);
    case Path:
        return QVariant(item.path);
    case Hide:
        return QVariant(item.hide);
    default:
        return QVariant();

    }


}

bool applications::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);


    QSettings desktopFile(SYSTEM_APPLICATIONS+aPath, QSettings::IniFormat);
    desktopFile.setIniCodec("UTF-8");

    desktopFile.beginGroup("App");
    ApplicationItem item;
    item.path = desktopFile.value("path").toString();
    item.icon = desktopFile.value("icon", "applications-all").toString();
    QString appDefName=desktopFile.value("name").toString();

    item.hide =desktopFile.value("hide",false).toBool();
    desktopFile.endGroup();
    desktopFile.beginGroup("Translations");

    //item.name = desktopFile.value(Language::getCurrentLanguage(),appDefName).toString();
    item.configPath=aPath;
    desktopFile.endGroup();



    appList.append(item);
    saveToSettings();

    endInsertRows();
    return true;
}

bool applications::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    appList.removeAt(row);
    saveToSettings();
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> applications::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Icon] = "appIcon";
    roles[Path] = "appPath";
    roles[Hide] = "isHide";

    return roles;
}

void applications::add(QString name)
{

    aPath =name;
    insertRows(appList.size(),1);


}
void applications::retranslate(QString language)
{
    Q_UNUSED(language);
    setActive(false);
    setActive(true);
}



void applications::remove(QString path)
{


    for(int i=0;i<appList.size();i++){
        ApplicationItem item =appList.at(i);

        if(item.configPath.compare(path) == 0) {
            removeRows(i,1);
            break;
        }
    }


}
bool applications::active()
{
    return m_active;
}
void applications::createAppsList(QStringList list,bool system){
    Q_UNUSED(system)
    for(int i=0;i<list.size();i++){
        QSettings desktopFile(SYSTEM_APPLICATIONS+list.at(i), QSettings::IniFormat);
        desktopFile.setIniCodec("UTF-8");
        desktopFile.beginGroup("App");
        ApplicationItem item;
        item.path = desktopFile.value("path").toString();

        item.icon = desktopFile.value("icon", "applications-all").toString();
        QString appDefName=desktopFile.value("name").toString();

        item.hide =desktopFile.value("hide",false).toBool();
        desktopFile.endGroup();
        desktopFile.beginGroup("Translations");

        item.name = desktopFile.value(m_language,appDefName).toString();
        item.configPath = list.at(i);
        desktopFile.endGroup();

        appList.append(item);



    }


}
void applications::setActive(const bool& active)
{

    beginResetModel();
    if( m_active==active) return;

    m_active=active;

    if(!active&&!appList.isEmpty()){

        appList.clear();

    }else{
        setLoading(true);
        //registerDBus();

        QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS","Applications");
        settings.beginGroup("Apps");
        int size =settings.beginReadArray("app");

        QStringList list;
        for(int i=0;i<size;i++){
            settings.setArrayIndex(i);
            list.append(settings.value("path").toString());

        }
        settings.endArray();
        settings.endGroup();
        createAppsList(list,false);


    }

    endResetModel();
    setLoading(false);
}

void applications::saveToSettings()
{


    QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS","Applications");
    settings.beginGroup("Apps");
    settings.remove("");
    //int size =settings.beginReadArray("apps");
    settings.beginWriteArray("app");
    for(int i=0;i<appList.size();i++){
        settings.setArrayIndex(i);
        settings.setValue("path",appList.at(i).configPath);
    }
    settings.endArray();
    settings.endGroup();
}

void applications::registerDBus()
{

    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.-Applications");
        return;
    }


    session.connect("", "/Applications", "com.kos.environment", "remove", this, SLOT(remove(QString)));
    session.connect("", "/Applications", "com.kos.environment", "add", this, SLOT(add(QString)));





    if(!session.registerObject("/Applications", this, QDBusConnection::ExportScriptableContents)) {
        //qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.environment")) {
        //qFatal("Cannot registerObject.");
        return;
    }
}

void applications::setLanguage(const QString &language)
{
    if(m_language !=language ){
        m_language = language;
        emit languageChanged();
    }
}

QString applications::language()
{
    return m_language;
}

void applications::setLoading(const bool &loading)
{
    if(m_loading !=loading){
        m_loading=loading;
        emit loadingChanged();
    }
}

bool applications::loading()
{
    return m_loading;
}
