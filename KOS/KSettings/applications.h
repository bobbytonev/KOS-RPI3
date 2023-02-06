/*
#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QDebug>
#include <QSettings>
#include <QDirIterator>
#include <QDir>
#include "language.h"
#include "applicationsthread.h"

class applications : public QAbstractListModel
{
    Q_OBJECT

    struct ApplicationItem
    {

        QString name,icon,path,category,confPath;
        double version;


    };

    Q_PROPERTY(bool active READ active WRITE setActive )

    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged )

    Q_PROPERTY(QString filterName READ filterName WRITE setFilterName )

    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";
    const QString USER_APPLICATIONS = QDir::homePath()+"/.local/share/shortcuts/";
public:
    enum {
        Name = Qt::UserRole,
        Icon,Path,Category,Version,ConfPath
    };

    explicit applications(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data: width:parent.width/2
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;


    void createAppsList(bool system);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE bool add(QString name);

    bool active();
    void setActive(const bool active);

    QString filter();
    void setFilter(const QString filter);

    QString filterName();
    void setFilterName(const QString filterName);

signals:
    void filterChanged();
public slots:
    void update();
    void updateAppLanguages(QString language);
private:
    QVector<ApplicationItem> appList;
    bool m_active =false;
    QString m_filter="";
    QString m_filterName="";
    QString aPath;

    QFileSystemWatcher appsWatcher;
    QString m_watcherPath;
    bool requestUpdate = true;
};

#endif // APPLICATIONS_H
*/
#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QAbstractListModel>
#include <applicationsthread.h>
#include "language.h"
#include "applicationsthread.h"

class applications : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active WRITE setActive )

    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged )

    Q_PROPERTY(QString filterCategory READ filterCategory WRITE setFilterCategory NOTIFY filterCategoryChanged)

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)


    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";
public:
    enum {
        Name = Qt::UserRole,
        Icon,ConfPath,AppPath
    };

    explicit applications(QObject *parent = nullptr);
    ~applications();
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;


    bool active();
    void setActive(const bool& active);

    bool running();
    void setRunning(const bool& running);


    QString filter();
    void setFilter(const QString& filter);

    QString filterCategory();
    void setFilterCategory(const QString& filterCategory);

    QString language();
    void setLanguage(const QString& language);

    Q_INVOKABLE void reset();

signals:
    void filterChanged();
    void filterCategoryChanged();
    void runningChanged();
    void languageChanged();
private:
    QList<ApplicationItem>* appList;
    applicationsthread appThread;

    bool m_active =false;
    bool m_running=false;

    QString m_filter="";
    QString m_filterCategory="";
    QString m_language;
   
    QThread* thread = NULL;

};

#endif // APPLICATIONS_H
