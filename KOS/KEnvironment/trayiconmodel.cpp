
#include "trayiconmodel.h"
#include "trayiconlist.h"

TrayIconModel::TrayIconModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{

}

int TrayIconModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant TrayIconModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    TrayIconItem item = mList->items().at(index.row());
       switch (role) {
       case AppName:
           return QVariant(item.appName).toString();
      case ImagePath:
            return QVariant(item.imagePath);
      case QmlLoaderPath:
            return QVariant(item.qmlPath);
       case Text:
            return QVariant(item.text);
       case ID:
            return QVariant(item.trayId).toInt();
       case ContextMenu:
            return QVariant(item.menus).toStringList();
       case ImageProvider:
           return QVariant(item.imageProvider).toBool();
       default:
            return QVariant();

       }
    return QVariant();
}

bool TrayIconModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //if (data(index, role) != value) {
        // FIXME: Implement me!
       // emit dataChanged(index, index, {role});
       // return true;
   // }
    return false;
}

Qt::ItemFlags TrayIconModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> TrayIconModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AppName] = "appName";
    roles[ImagePath] = "imagePath";
    roles[QmlLoaderPath] = "qmlLoaderPath";
    roles[ID] = "trayId";
    roles[Text] = "bodyText";
    roles[ContextMenu] = "menus";
    roles[ImageProvider] ="imageProvider";

    return roles;
}

void TrayIconModel::setList(TrayIconList *list)
{

    beginResetModel();

    if(mList) list->disconnect(this);

    mList=list;

    if(mList){
        connect(list,&TrayIconList::preTrayIconRemoved,this,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(list,&TrayIconList::postTrayIconRemoved,this,[=](){
            endRemoveRows();
        });
        connect(list,&TrayIconList::preTrayIconAppended,this,[=](){
            const int index  =mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(list,&TrayIconList::postTrayIconAppended,this,[=](){
            endInsertRows();
        });
        connect(list,&TrayIconList::trayIconChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ID,ImagePath,ContextMenu,Text,ImageProvider});


        });
        connect(list,&TrayIconList::iconChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ImagePath});


        });

    }

    endResetModel();

}

TrayIconList *TrayIconModel::list() const
{
    return mList;
}


/*
#include "trayiconmodel.h"
#include "trayiconlist.h"

TrayIconModel::TrayIconModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{

}

int TrayIconModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant TrayIconModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    //TrayIconItem item = mList->items().at(index.row());

    switch (role) {
    //  case AppName:
    //    return QVariant(item.appName).toString();

    case ImagePath:
        return mList->items().values().at(index.row())->imagePath();
    case Text:
        return mList->items().values().at(index.row())->text();
    case ID:
        return mList->items().values().at(index.row())->trayId();
    case ContextMenu:
        return mList->items().values().at(index.row())->menus();
    case ImageProvider:
        return true;
    default:
        return QVariant();

    }
    return QVariant();
}

bool TrayIconModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //if (data(index, role) != value) {
    // FIXME: Implement me!
    // emit dataChanged(index, index, {role});
    // return true;
    // }
    return false;
}

Qt::ItemFlags TrayIconModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> TrayIconModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    //  roles[AppName] = "appName";
    roles[ImagePath] = "imagePath";
    //roles[QmlLoaderPath] = "qmlLoaderPath";
    roles[ID] = "trayId";
    roles[Text] = "bodyText";
    roles[ContextMenu] = "menus";
    roles[ImageProvider] ="imageProvider";

    return roles;
}

void TrayIconModel::setList(TrayIconList *list)
{

    beginResetModel();

    if(mList) list->disconnect(this);

    mList=list;

    if(mList){
        connect(list,&TrayIconList::preTrayIconRemoved,this,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(list,&TrayIconList::postTrayIconRemoved,this,[=](){
            endRemoveRows();
        });
        connect(list,&TrayIconList::preTrayIconAppended,this,[=](){
            const int index  =mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(list,&TrayIconList::postTrayIconAppended,this,[=](){
            endInsertRows();
        });
        connect(list,&TrayIconList::textChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {Text});


        });
        connect(list,&TrayIconList::imagePathChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ImagePath});


        });
        connect(list,&TrayIconList::menusChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ContextMenu});


        });
        connect(list,&TrayIconList::trayIdChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ID});


        });

    }

    endResetModel();

}

TrayIconList *TrayIconModel::list() const
{
    return mList;
}

*/
