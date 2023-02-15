#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QAbstractListModel>
#include <QFileInfo>
#include <QSettings>
#include <QDir>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>


class applications : public QAbstractListModel
{
    Q_OBJECT

    struct ApplicationItem
    {

        QString name,icon,path,configPath="";
        bool hide=false;

    };

    Q_PROPERTY(bool active READ active WRITE setActive )
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

    Q_PROPERTY(bool loading READ loading WRITE setLoading NOTIFY loadingChanged)

    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";

public:
    enum {
        Name = Qt::UserRole,
        Icon,Path,Hide
    };

    explicit applications(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;


    void createAppsList(QStringList value,bool system);



    Q_INVOKABLE void retranslate(QString language);

    bool active();
    void setActive(const bool& active);
    void saveToSettings();
    void registerDBus();

    void setLanguage(const QString& language);
    QString language();

    void setLoading(const bool& loading);
    bool loading();
signals:
    void languageChanged();
    void loadingChanged();

public slots:
    Q_SCRIPTABLE void remove(QString path);
    Q_SCRIPTABLE void add(QString name);
private:
    QVector<ApplicationItem> appList;
    bool m_active =false;
    QString m_language;
    QString aPath;
    QDBusConnection session = QDBusConnection::sessionBus();
    bool m_loading;


};

#endif // APPLICATIONS_H
