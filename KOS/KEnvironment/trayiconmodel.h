
#ifndef TRAYICONMODEL_H
#define TRAYICONMODEL_H

#include <QAbstractListModel>


class TrayIconList;

class TrayIconModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(TrayIconList *list READ list WRITE setList)

public:
    enum {
        AppName = Qt::UserRole,
        ImagePath,QmlLoaderPath,ID,Text,ContextMenu,ImageProvider

    };

    explicit TrayIconModel(QObject *parent = nullptr);

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

    TrayIconList *list() const;
    void setList(TrayIconList *list);



private:
    TrayIconList *mList;
};

#endif // TRAYICONMODEL_H


/*
#ifndef TRAYICONMODEL_H
#define TRAYICONMODEL_H

#include <QAbstractListModel>


class TrayIconList;

class TrayIconModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(TrayIconList *list READ list WRITE setList)

public:
    enum {
        AppName = Qt::UserRole,
        ImagePath,QmlLoaderPath,ID,Text,ContextMenu,ImageProvider

    };

    explicit TrayIconModel(QObject *parent = nullptr);

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

    TrayIconList *list() const;
    void setList(TrayIconList *list);



private:
    TrayIconList *mList;
};

#endif // TRAYICONMODEL_H

*/
