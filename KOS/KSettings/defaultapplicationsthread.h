#ifndef DEFAULTAPPLICATIONSTHREAD_H
#define DEFAULTAPPLICATIONSTHREAD_H

#include <QObject>
#include <QThread>
#include <QSettings>
#include <QDir>
#include <QDebug>
struct DefaultApps
{

    QString category,name,icon,config,path,mimetypeName,suffix;



};
class DefaultApplicationsThread : public QThread
{
    Q_OBJECT
public:
    DefaultApplicationsThread();
    ~DefaultApplicationsThread();
    QString getAppName(QString config);
    QList<DefaultApps>* getDefaultAppList();

    void setLanguage(const QString& lang);

public slots:
    void reset(bool extended);
    void changeData(int index, QString appConfig, QString path, QString icon);
    void removeItem(int index);
    void saveToSettings(int index);
    void addItem(QString group,QString mimetype);
    void removeFromSettings(QString group);
signals:
    void beginReset();
    void endReset();
    void running(bool running);
    void dataChanged(int index);
    void preItemRemoved(int index);
    void postItemRemoved();
    void preItemAdded(int size);
    void postItemAdded();

private:
    QList<DefaultApps> defaultApps;
    bool m_extended;
    QString language;

};

#endif // DEFAULTAPPLICATIONSTHREAD_H
