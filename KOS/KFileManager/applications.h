#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QAbstractListModel>
#include <QDebug>
#include "applicationthread.h"



class applications : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active WRITE setActive )

    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged )

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged )

    const QString  SYSTEM_APPLICATIONS = "/usr/share/applications/";
public:
    enum {
        Name = Qt::UserRole,
        Icon,Path
    };

    explicit applications(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;




    bool active();
    void setActive(const bool& active);

    int state();
    void setState(const int& state);


    QString filter();
    void setFilter(const QString& filter);

    Q_INVOKABLE void startApplication(const QString& file);



signals:
    void filterChanged();
    void stateChanged();
    void loadEnded(bool result);
private:
    QVector<ApplicationItem> appList;

    bool m_active =false;
    int m_state=0;

    QString m_filter="";
    ApplicationThread appThread;




};

#endif // APPLICATIONS_H
