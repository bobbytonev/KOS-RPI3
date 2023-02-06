#include "applications.h"

applications::applications(QObject *parent)
    : QAbstractListModel(parent)
{

    thread =new QThread(this);
    appList = appThread.getAppList();
    appThread.moveToThread(thread);
    //;
}
applications::~applications(){
    delete thread;
}
int applications::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() && appList == NULL)
        return 0;

    return appList->size();
}

QVariant applications::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && appList == NULL)
        return QVariant();

    ApplicationItem item = appList->at(index.row());
    switch (role) {
    case Name:
        return QVariant(item.name).toString();
    case Icon:
        return QVariant(item.icon);
    case ConfPath:
        return QVariant(item.confPath);
    case AppPath:
        return QVariant(item.appPath);

    default:
        return QVariant();

    }


}
QHash<int, QByteArray> applications::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Icon] = "appIcon";
    roles[ConfPath]="confPath";
    roles[AppPath]="appPath";

    return roles;
}

bool applications::active()
{
    return m_active;
}

void applications::setActive(const bool& active)
{


    if( m_active==active) return;

    m_active=active;

    if(active){

        connect(&appThread,&applicationsthread::runningChanged,this,&applications::setRunning);
        connect(&appThread,&applicationsthread::beginReset,this,[=](){
            beginResetModel();

        });
        connect(&appThread,&applicationsthread::endReset,this,[=](){
            endResetModel();
        });

        appThread.reset(m_filter,m_filterCategory,m_language);

    }else{
        disconnect(&appThread,&applicationsthread::runningChanged,this,&applications::setRunning);
    }




}

bool applications::running()
{
    return m_running;
}

void applications::setRunning(const bool &running)
{
    if(m_running != running){
        m_running = running;
        emit runningChanged();
    }

}

QString applications::language()
{
    return m_language;
}

void applications::setLanguage(const QString &language)
{
    if(m_language!=language){
        m_language=language;
        emit languageChanged();

    }
}

QString applications::filter()
{
    return m_filter;
}

void applications::setFilter(const QString &filter)
{
    if(m_filter!=filter){
        m_filter=filter;
        reset();

    }
}
QString applications::filterCategory()
{
    return m_filterCategory;
}

void applications::setFilterCategory(const QString &filterCategory)
{
    if(m_filterCategory!=filterCategory){
        m_filterCategory=filterCategory;
        emit filterCategoryChanged();
    }

}

void applications::reset()
{
    appThread.reset(m_filter,m_filterCategory,m_language);
}


