#ifndef NOTIFICATIONMODEL_H
#define NOTIFICATIONMODEL_H

#include <QAbstractListModel>



class NotificationsList;

class NotificationModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(NotificationsList *list READ list WRITE setList)

public:
    enum {
        AppName = Qt::UserRole,
        ImagePath,QmlLoaderPath,ID,Text,ContextMenu,Title,Priority,ImageProvider

    };
    explicit NotificationModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    //bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
   //bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    NotificationsList *list() const;
    void setList(NotificationsList *list);



private:
    NotificationsList *mList;
};

#endif // NOTIFICATIONMODEL_H
