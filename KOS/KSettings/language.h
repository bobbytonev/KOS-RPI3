#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QTranslator>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
class Language : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
public:
    Language( QQmlEngine* engine);
    ~Language();




    QString language();
    void setLanguage(const QString language);
    void init();
    void installNewTransition(QString language);


signals:
    void languageChanged(QString currentLanguage);

public slots:
    void updateLanguage(QString language);

private:
    QString m_language;
    QString watcherPath;
    QTranslator* translator;
    QQmlEngine* m_engine;
    QString LANGUAGE_FOLDER ="/opt/com.kos.settings/";



};

#endif // LANGUAGE_H
