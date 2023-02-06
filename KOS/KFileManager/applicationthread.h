#ifndef APPLICATIONTHREAD_H
#define APPLICATIONTHREAD_H

#include <QObject>
#include <QThread>
#include <QDirIterator>
#include <QSettings>
#include <QMimeDatabase>
#include <QMimeType>
#include <QDebug>
#include "launcher.h"

//only for tests
#include <QProcess>
struct ApplicationItem
{

    QString name,icon,path;

};
class ApplicationThread : public QObject
{
    Q_OBJECT
public:
    ApplicationThread();
    ~ApplicationThread();

public slots:
    void load(const QString& filter);
    bool startApp(QString filePath);
    void setList(QVector<ApplicationItem> *appList);



signals:
    void beginInsert();
    void endInsert();
    void beginReset();
    void endReset();
    void loadEnded(bool result);

private:
    QThread thread;
    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";
    QVector<ApplicationItem> *m_appList=NULL;
    Launcher launcher;
};

#endif // APPLICATIONTHREAD_H
