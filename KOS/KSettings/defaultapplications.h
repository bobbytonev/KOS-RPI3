#ifndef DEFAULTAPPLICATIONS_H
#define DEFAULTAPPLICATIONS_H

#include <QAbstractListModel>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include "language.h"
#include "defaultapplicationsthread.h"
class DefaultApplications : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool extended READ extended WRITE setExtended NOTIFY extendedChanged )
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged )

    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)


public:
    enum {
        Name = Qt::UserRole,
        Icon,Path,Category,Mimetype,Suffix,Config
    };


    explicit DefaultApplications(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    //bool setData(const QModelIndex &index, const QVariant &value,
                 //int role = Qt::EditRole) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    bool extended();
    void setExtended(const bool& extended);

    bool running();
    void setRunning(const bool& running);

    QString language();
    void setLanguage(const QString& language);

    //QString getAppName(QString config);

    //bool dublicate(QString app);


    //Q_INVOKABLE void saveToSettings(int index);


    //Q_INVOKABLE void add(QString name);
    //Q_INVOKABLE void remove(int index);

    Q_INVOKABLE void changeData(int index, QString appConfig, QString path, QString icon);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void addItem(QString groupName,QString mimetype);

signals:
    void extendedChanged();
    void runningChanged();
    void languageChanged();
private:
    bool m_extended=false;
    bool m_running = false;
    QList<DefaultApps> *defAppList=NULL;
    DefaultApplicationsThread defAppsThread;
    QString m_language;

};

#endif // DEFAULTAPPLICATIONS_H
