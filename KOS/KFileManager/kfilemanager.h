#ifndef KFILEMANAGER_H
#define KFILEMANAGER_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
class KFileManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(int max READ max NOTIFY maxChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
public:
    KFileManager();

    void sendDbusMethod(QString methodName,const QVariantList& list);

    int max();
    int progress();
    bool running();

    QVariant setProperties(QString method);


    Q_INVOKABLE void copy(QString path,QStringList fileNames,QString destination);
    Q_INVOKABLE void move(QString path,QStringList fileNames,QString destination);
    Q_INVOKABLE void rename(QString filePath, QString newName);
    Q_INVOKABLE void remove(QStringList files);
    Q_INVOKABLE void createFolder(QString path);
signals:
    void copyFinished();
    void moveFinished();
    void renameFinished();
    void deleteFinished();
    void progressChanged();
    void maxChanged();
    void runningChanged();
public slots:
    void setProgress(int progress);
    void setMax(int max);
    void setRunning(bool running);

private:
    int m_progress;
    int m_max;
    bool m_running;

};

#endif // KFILEMANAGER_H
