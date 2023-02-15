#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QObject>
#include <QQmlPropertyMap>
#include <QQuickStyle>
#include <QDebug>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include <QIcon>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QQmlEngine>
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


    Q_INVOKABLE void changeStyle(QString style,bool iconPack);
    Q_INVOKABLE void overrideProperty(QString key,QString value);



    int size();
    QStringList get(int index);




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
    QDBusConnection conn=  QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.stylemanager");

};

#endif // STYLEMANAGER_H
