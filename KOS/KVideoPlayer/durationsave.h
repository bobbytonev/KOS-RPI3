#ifndef DURATIONSAVE_H
#define DURATIONSAVE_H

#include <QObject>
#include "durationsavethread.h"
class DurationSave : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
public:
    DurationSave();

    int progress() const;

    void setSource(const QString& source);
    QString source() const;

    void setActive(const bool& active);
    bool active() const;

    Q_INVOKABLE void saveProgress(int progress);
signals:
    void progressChanged();
    void sourceChanged();
    void activeChanged();
public slots:
    void setProgress( int progress);


private:
    int m_progress;
    bool m_active;
    QString m_source;
    DurationSaveThread dst;

};

#endif // DURATIONSAVE_H
