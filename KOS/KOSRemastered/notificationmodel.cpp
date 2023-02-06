#include "notificationmodel.h"
#include "notificationslist.h"
NotificationModel::NotificationModel(QObject *parent)
    : QAbstractListModel(parent), mList(nullptr)
{
}

int NotificationModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;


    return mList->items().size();
}

QVariant NotificationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    NotificationItem item = mList->items().at(index.row());
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
            return QVariant(item.notifyId).toInt();
       case ContextMenu:
            return QVariant(item.buttons).toStringList();
       case Title:
            return QVariant(item.title).toString();
       case Priority:
            return QVariant(item.priority).toInt();
       case ImageProvider:
           return QVariant(item.imageProvider).toBool();
       default:
            return QVariant();

       }

}

bool NotificationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags NotificationModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}


/*
bool NotificationModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool NotificationModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}
*/
QHash<int, QByteArray> NotificationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AppName] = "appName";
    roles[ImagePath] = "imagePath";
    roles[QmlLoaderPath] = "qmlLoaderPath";
    roles[ID] = "notifyId";
    roles[Text] = "bodyText";
    roles[ContextMenu] = "buttons";
    roles[Title] = "title";
    roles[Priority] = "priority";
    roles[ImageProvider] = "imageProvider";

    return roles;
}
void NotificationModel::setList(NotificationsList *list)
{


    beginResetModel();

    if(mList) list->disconnect(this);

    mList=list;

    if(mList){
        connect(list,&NotificationsList::preNotificationRemoved,this,[=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(list,&NotificationsList::postNotificationRemoved,this,[=](){
            endRemoveRows();
        });
        connect(list,&NotificationsList::preNotificationAppended,this,[=](){
            const int index  =mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(list,&NotificationsList::postNotificationAppended,this,[=](){
            endInsertRows();
        });
        connect(list,&NotificationsList::notificationChanged,this,[=](int index){
            QModelIndex item =createIndex(index,index);
            emit dataChanged(item, item, {ImagePath,Text,QmlLoaderPath,ContextMenu,Title,ImageProvider,Priority});


        });

    }

    endResetModel();

}

NotificationsList *NotificationModel::list() const
{
    return mList;
}

