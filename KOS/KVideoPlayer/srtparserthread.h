#ifndef SRTPARSERTHREAD_H
#define SRTPARSERTHREAD_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <QTime>

class SrtParserThread : public QObject
{
    Q_OBJECT
    struct SrtItem{
        QString text;
        int startTime;
        int endTime;

    };
public:
    SrtParserThread();
    ~SrtParserThread();

signals:
    void subUpdated(QString subtitle);

public slots:
    void openFile(QString filePath,QString codec);
    void positionChanged(int position);

private:
    QList<SrtItem> srtData;
    QThread thread;
};

#endif // SRTPARSERTHREAD_H
