#include "internalfiles.h"

#include <QFileInfo>

InternalFiles::InternalFiles(QObject *parent)
    : QAbstractListModel(parent)
{


}

int InternalFiles::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;


    return size();//audioList.size();
}

QVariant InternalFiles::data(const QModelIndex &index, int role) const
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

Qt::ItemFlags InternalFiles::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> InternalFiles::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[FileUrl] = "fileUrl";
    roles[FileName] = "fileName";

    return roles;
}

void InternalFiles::activate()
{
    /*
    int audioListSize = size(m_type);
    for(int i=0;i<audioListSize;i++){
        AudioItem item;
        item.fileUrl = get(i,m_type);
        item.fileName = getFileName(item.fileUrl);
        audioList.append(item);
    }
    */


    QDBusConnection conn = QDBusConnection::connectToBus(QDBusConnection::SystemBus,"com.kos.filecache");
    conn.connect("", m_type, "com.kos.filecache","fileRemoved",this,SLOT(fileRemoved(int,QString)));

    conn.connect("", m_type, "com.kos.filecache","fileAdded",this,SLOT(fileAdded(QString)));
    conn.connect("", m_type, "com.kos.filecache","fileRenamed",this,SLOT(fileRenamed(int,QString,QString)));

}

QString InternalFiles::getFileName(QString path)
{
    QFileInfo fileInfo(path);
    return fileInfo.fileName();

}

QString InternalFiles::get(int index) const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filecache",m_type,"","get");
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

int InternalFiles::size() const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.filecache",m_type,"","size");
    QList<QVariant> args;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        return list.at(0).toInt();
    }
    return -1;
}

QString InternalFiles::type()
{
    return m_type;
}

void InternalFiles::setType(QString type)
{
    m_type = type;
    emit typeChanged();
    activate();

}

void InternalFiles::fileRemoved(int index, QString path)
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

void InternalFiles::fileAdded(QString path)
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

void InternalFiles::fileRenamed(int index, QString oldPath, QString newPath)
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
