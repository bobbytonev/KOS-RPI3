#ifndef APPLICATIONSTHREAD_H
#define APPLICATIONSTHREAD_H

#include <QThread>
#include <QObject>
#include <QDirIterator>
#include <QSettings>
struct ApplicationItem
{

    QString name,icon,confPath,appPath;



};

class applicationsthread : public QObject
{
    Q_OBJECT

public:
    explicit applicationsthread(QObject *parent = nullptr);
    ~applicationsthread();
    QList<ApplicationItem>* getAppList();

signals:
    void appRemovedBegin();
    void appRemovedEnd(int index);
    void appAddedBegin();
    void addAddedEnd();
    void beginReset();
    void endReset();
    void runningChanged(bool running);
public slots:
    void reset(const QString& filter,const QString& filterCategory,const QString& language);
private:
    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";
    QList<ApplicationItem> appList;

};

#endif // APPLICATIONSTHREAD_H
