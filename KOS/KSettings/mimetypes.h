#ifndef MIMETYPES_H
#define MIMETYPES_H

#include <QAbstractListModel>
#include <QMimeDatabase>
class mimetypes : public QObject
{
    Q_OBJECT


    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)


public:
    mimetypes();
    bool running();
    void setRunning(bool running);
    Q_INVOKABLE QStringList getMimetype(QString suffix);

signals:
    void runningChanged();
    void requestMimetype(QString suffix);
    void mimetypeChanged(QStringList mimeType);
public slots:
    void getMimeType(QString suffix);
private:
    bool m_running;
    QMimeDatabase database;
};

#endif // MIMETYPES_H
