#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QSettings>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDebug>

class Language : public QObject
{
    Q_OBJECT
public:
    explicit Language(QObject *parent = nullptr);

    void getLanguageFromSettings();
    void languageChanged();
    void saveToSettings();


public slots:
    Q_SCRIPTABLE QString getLanguage();
    Q_SCRIPTABLE void setLanguage(QString language);
    Q_SCRIPTABLE int size();
    Q_SCRIPTABLE QStringList languageAt(int index);

private:
    QString currentLanguage;
    QDBusConnection session = QDBusConnection::systemBus();
    QList<QStringList> languageList;

};

#endif // LANGUAGE_H
