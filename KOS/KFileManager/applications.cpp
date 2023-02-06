#include "applications.h"

applications::applications(QObject *parent)
    : QAbstractListModel(parent)
{

    appThread.setList(&appList);

}
int applications::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return appList.size();
}

QVariant applications::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ApplicationItem item = appList.at(index.row());
    switch (role) {
    case Name:
        return QVariant(item.name).toString();
    case Icon:
        return QVariant(item.icon);
    case Path:
        return QVariant(item.path);
    default:
        return QVariant();

    }


}


QHash<int, QByteArray> applications::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Icon] = "appIcon";
    roles[Path] = "appPath";
    return roles;
}

bool applications::active()
{
    return m_active;
}

void applications::setActive(const bool& active)
{

    if(m_active==active) return;

    m_active = active;

    if(m_active){
        connect(&appThread,&ApplicationThread::beginReset,this,[=](){
            beginResetModel();
            setState(1);
        });
        connect(&appThread,&ApplicationThread::endReset,this,[=](){
           endResetModel();
           setState(0);
        });
        connect(&appThread,&ApplicationThread::loadEnded,this,&applications::loadEnded);
    }else{

    }

}
void applications::setState(const int &state){
    if(m_state !=state){
        m_state = state;
        emit stateChanged();
    }

}
int applications::state(){
    return m_state;
}

QString applications::filter()
{
    return m_filter;
}

void applications::setFilter(const QString& filter)
{
    if(m_filter!=filter){
        m_filter=filter;
        emit filterChanged();
    }

}

void applications::startApplication(const QString &file)
{
     appThread.startApp(file);
}


