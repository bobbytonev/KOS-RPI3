#include "internalmusic.h"

#include <QFileInfo>

InternalMusic::InternalMusic(QObject *parent)
    : QAbstractListModel(parent)
{

    activate();
}

int InternalMusic::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;


    return size();//audioList.size();
}

QVariant InternalMusic::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    //AudioItem item = audioList.at(index.row());
    QString fileName =get(index.row());
    switch (role) {
    case FileUrl:
        return "file:///"+QVariant(fileName).toString();//QVariant(item.fileUrl).toString();
    case FileName:
    {
        QFileInfo fileInfo(fileName);
        return fileInfo.fileName();
        // return //fileName;//QVariant(item.fileName).toString();
    }
    default:
        return QVariant();

    }
}

Qt::ItemFlags InternalMusic::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> InternalMusic::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[FileUrl] = "fileUrl";
    roles[FileName] = "fileName";

    return roles;
}

void InternalMusic::activate()
{
    /*
    int audioListSize = size(FILE_TYPE);
    for(int i=0;i<audioListSize;i++){
        AudioItem item;
        item.fileUrl = get(i,FILE_TYPE);
        item.fileName = getFileName(item.fileUrl);
        audioList.append(item);
    }
    */


    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.filecache");
    conn.connect("", FILE_TYPE, "com.kos.filecache","fileRemoved",this,SLOT(fileRemoved(int,QString)));

    conn.connect("", FILE_TYPE, "com.kos.filecache","fileAdded",this,SLOT(fileAdded(QString)));
    conn.connect("", FILE_TYPE, "com.kos.filecache","fileRenamed",this,SLOT(fileRenamed(int,QString,QString)));

}

QString InternalMusic::getFileName(QString path)
{
    QFileInfo fileInfo(path);
    return fileInfo.fileName();

}

QString InternalMusic::get(int index) const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filecache",FILE_TYPE,"","get");
    QList<QVariant> args;
    args<<index;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toString();
    }
    return "";

}

int InternalMusic::size() const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filecache",FILE_TYPE,"","size");
    QList<QVariant> args;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        return list.at(0).toInt();
    }
    return -1;
}

void InternalMusic::fileRemoved(int index, QString path)
{

    // if(index < 0 || index >= audioList.size()) return;


    //  AudioItem item = audioList.at(index);
    //if(item.fileUrl.compare(path) == 0){
    //  audioList.removeAt(index);
    Q_UNUSED(path);
    beginRemoveRows(QModelIndex(),index,index);
    endRemoveRows();
    //}



}

void InternalMusic::fileAdded(QString path)
{

    if(!path.isEmpty() ){
        const int index =size()-1;
        //AudioItem item;
        //item.fileUrl = path;
        //item.fileName =getFileName(path);
        //audioList.append(item);
        beginInsertRows(QModelIndex(),index,index);
        endInsertRows();

    }


}

void InternalMusic::fileRenamed(int index, QString oldPath, QString newPath)
{
    //if(index < 0 || index >= audioList.size()) return;



    //AudioItem item = audioList.at(index);
    //if(item.fileUrl.compare(oldPath) == 0){
    //  item.fileUrl = newPath;
    // item.fileName = getFileName(newPath);
    //audioList[index] = item;
    Q_UNUSED(oldPath);
    Q_UNUSED(newPath);
    QModelIndex item =createIndex(index,index);
    emit dataChanged(item, item, {FileUrl,FileName});


    //}




}
