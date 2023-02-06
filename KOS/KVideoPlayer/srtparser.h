#ifndef SRTPARSER_H
#define SRTPARSER_H
#include <QObject>
#include <QTextCodec>
#include "srtparserthread.h"


class SrtParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString subtitle READ subtitle NOTIFY subtitleChanged)

    Q_PROPERTY(QString subFile READ subFile WRITE setSubFile)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(int videoPosition READ videoPosition WRITE setVideoPosition)
    Q_PROPERTY(QString codec READ codec WRITE setCodec NOTIFY codecChanged)



public:
    SrtParser();

    QString subtitle();


    QString subFile();
    void setSubFile(QString subtitle);

    int status();

    int videoPosition();
    void setVideoPosition(int videoPosition);

    QString codec();
    void setCodec(QString codec);




signals:
    void subtitleChanged();
    void statusChanged();
    void subFileChanged(QString subFile,QString codec);
    void positionChanged(int position);
    void codecChanged();


public slots:
     void setSubtitle(QString subtitle);

private:

    QString m_subtitle;
    QString m_subFile;
    int m_videoPosition;
    int m_status;

    SrtParserThread thread;
    QString m_codec;


};

#endif // SRTPARSER_H
