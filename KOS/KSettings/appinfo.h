#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>
#include <QSettings>
class AppInfo : public QObject
{


    Q_OBJECT
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QStringList info READ info NOTIFY infoChanged)


    Q_PROPERTY(QString configPath READ configPath WRITE setConfigPath)
public:
    explicit AppInfo(QObject *parent = nullptr);

    void setName(const QString& name);
    QString name();

    void setIcon(const QString& icon);
    QString icon();

    void setConfigPath(const QString& configPath);
    QString configPath();

    void setInfo(const QStringList& info);
    QStringList info();


signals:
    void infoChanged();
    void iconChanged();
    void nameChanged();

private:
    QString m_icon;
    QString m_name;
    QString m_configPath;
    QStringList m_info;
};

#endif // APPINFO_H
