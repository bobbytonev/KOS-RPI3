#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QObject>
#include <QQmlPropertyMap>
#include <QQuickStyle>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include <QIcon>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusArgument>
#include <QDBusObjectPath>
class StyleManager :public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool icon_pack_reset READ icon_pack_reset WRITE setIconPackReset NOTIFY iconPackResetChanged)
public:
    StyleManager();

    Q_INVOKABLE QString styleName();
    Q_INVOKABLE QString iconPack();


    QString getStyleFromSettings();

    void setIconPack(QString iconPack);

    void loadStyleConfig();
    QString getSystemStyle(bool iconPack);

    bool icon_pack_reset();
    void setIconPackReset(const bool &a);





    //test
    int size();
    QStringList get(int index);
    //test

    QQmlPropertyMap data;

signals:
    void iconPackResetChanged();

public slots:
    void changeProperty(QString key, QString value);
    void styleChange(QString path);
    void iconChange(QString path);


private:
    const QString STYLES_FOLDER =  "/usr/share/themes/";
    const QStringList ICONS_FOLDER =  {"/usr/share/icons/"};
    bool m_icon_pack_reset=false;
    QString m_icon_pack;
    QString m_styleName;
    QDBusConnection conn=QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.stylemanager");

};

#endif // STYLEMANAGER_H
