#ifndef DURATIONSAVETHREAD_H
#define DURATIONSAVETHREAD_H

#include <QObject>
#include <QFile>
#include <QThread>
#include <QTimer>
#include <QDebug>
class DurationSaveThread : public QObject
{
    Q_OBJECT
public:
    DurationSaveThread();
    ~DurationSaveThread();

    void saveProgress(int progress);

    void stopThread();
    void startThread();
public  slots:
    void getProgress(QString source);
signals:
    void progressChanged(int progress);

private:
    QThread thread;
    int m_progress;
    bool isSaved=false;
    QString m_source;

};

#endif // DURATIONSAVETHREAD_H
