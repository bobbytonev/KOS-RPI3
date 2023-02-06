#ifndef MIMETYPETHREAD_H
#define MIMETYPETHREAD_H

#include <QObject>
#include <QThread>
class mimetypethread : public QObject
{
    Q_OBJECT
public:
    explicit mimetypethread(QObject *parent = nullptr);

signals:
public slots:
    //void reload(int startIndex,int dataCount);

public:
    QThread thread;
};

#endif // MIMETYPETHREAD_H
