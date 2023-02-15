#include "stylemanager.h"

StyleManager::StyleManager()
{

    QIcon::setThemeSearchPaths(ICONS_FOLDER);

    QIcon::setFallbackThemeName("candy-icons");

    if(!conn.connect("", "/", "com.kos.stylemanager","styleNameChanged",this,SLOT(styleChange(QString))))
        qFatal("Cannot register style manager");

    conn.connect("", "/", "com.kos.stylemanager","propertyChanged",this,SLOT(changeProperty(QString,QString)));
    conn.connect("", "/", "com.kos.stylemanager","iconPackChanged",this,SLOT(iconChange(QString)));

    QIcon::setThemeName(getSystemStyle(true));


    QString style =STYLES_FOLDER+getSystemStyle(false); // bool value for iconPack
    QQuickStyle::setStyle(style);

    //QQmlEngine::addImportPath("/usr/share/themes/"+style+"/files");


    loadStyleConfig();

}

QString StyleManager::styleName()
{

    return QQuickStyle::name();
}

QString StyleManager::iconPack()
{
    return QIcon::themeName();
}
void StyleManager::setIconPack(QString iconPack)
{
    setIconPackReset(true);
    QIcon::setThemeName(iconPack);
    setIconPackReset(false);
}

void StyleManager::loadStyleConfig()
{
    int cfgSize = size();
    for(int i=0;i<cfgSize;i++){
        QStringList list = get(i);
        data.insert(list.at(0),QVariant(list.at(1)));
    }

}

QString StyleManager::getSystemStyle(bool iconPack)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/", "", iconPack ? "iconPackName":"appStyleName");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();


    return !list.isEmpty() ? list.at(0).toString() : "";
}

void StyleManager::changeProperty(QString key,QString value)
{
    //QVariant val = QVariant::fromValue(QVariantList{group,value});
    QVariant var = QVariant::fromValue(value);
    data.insert(key,var);
    emit data.valueChanged(key,var);
}
void StyleManager::iconChange(QString path)
{
    setIconPack(path);
}
void StyleManager::styleChange(QString path)
{
    Q_UNUSED(path);
    QCoreApplication::quit();
    exit(0);
}
bool StyleManager::icon_pack_reset() {
    return m_icon_pack_reset;
}

void StyleManager::setIconPackReset(const bool &a) {
    if (a != m_icon_pack_reset) {
        m_icon_pack_reset = a;
        emit iconPackResetChanged();
    }
}

void StyleManager::changeStyle(QString style, bool iconPack)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager", "/","",iconPack ? "setIconPackName":"setAppStyleName");
    QList<QVariant> args;
    args.append(style);
    m.setArguments(args);
    QDBusConnection::systemBus().asyncCall(m);
}
void StyleManager::overrideProperty(QString key,QString value)
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager", "/","","changeProperty");
    QList<QVariant> args;
    args.append(key);
    args.append(value);
    m.setArguments(args);
    QDBusConnection::systemBus().asyncCall(m);
}

int StyleManager::size()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/", "", "size");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();


    return !list.isEmpty() ? list.at(0).toInt() : -1;
}

QStringList StyleManager::get(int index)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/", "", "get");
    QList<QVariant> arguments;
    arguments.append(index);
    m.setArguments(arguments);
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();


    return  list.at(0).toStringList();
}
