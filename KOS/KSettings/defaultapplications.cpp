#include "defaultapplications.h"

DefaultApplications::DefaultApplications(QObject *parent)
    : QAbstractListModel(parent)
{

    defAppList = defAppsThread.getDefaultAppList();

}
int DefaultApplications::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() && defAppList == NULL)
        return 0;

    return defAppList->size();
}

QVariant DefaultApplications::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && defAppList == NULL)
        return QVariant();

    DefaultApps item = defAppList->at(index.row());
    switch (role) {
    case Name:
        return QVariant(item.name).toString();
    case Icon:
        return QVariant(item.icon);
    case Path:
        return QVariant(item.path);
    case Category:
        return QVariant(item.category);
    case Mimetype:
        return QVariant(item.mimetypeName);
    case Suffix:
        return QVariant(item.suffix);
    case Config:
        return QVariant(item.config);

    default:
        return QVariant();




    }

}
/*
            bool DefaultApplications::setData(const QModelIndex &index, const QVariant &value, int role)
            {
                if (data(index, role) != value) {




                   DefaultApps item = defAppList.at(index.row());

                    switch (role) {
                    case Name:
                        item.name=value.toString();
                        break;
                   case Icon:
                            item.icon=value.toString();
                                break;
                   case Path:
                         item.path=value.toString();
                              break;
                    case Category:
                             item.category=value.toString();
                    case Config:
                             item.config=value.toString();
                                 break;


                    }
                    defAppList.replace(index.row(),item);

                        emit dataChanged(index, index, {role});
                    return true;
                }
                return false;
            }

            Qt::ItemFlags DefaultApplications::flags(const QModelIndex &index) const
            {
                if (!index.isValid())
                    return Qt::NoItemFlags;

                return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
            }

            bool DefaultApplications::insertRows(int row, int count, const QModelIndex &parent)
            {
                beginInsertRows(parent, row, row + count - 1);

                DefaultApps item;
                QString extendedName =m_name;

                if(!m_extended)
                item.category=extendedName;
                else{
                    QStringList groupNameSplit =extendedName.split(" ");
                    item.category=groupNameSplit.at(0);
                    item.mimetypeName= groupNameSplit.size()>1 ? groupNameSplit.at(1) :" ";

                }



                defAppList.append(item);
                saveToSettings(defAppList.size()-1);
                endInsertRows();
                return true;
            }

            bool DefaultApplications::removeRows(int row, int count, const QModelIndex &parent)
            {
                beginRemoveRows(parent, row, row + count - 1);
                defAppList.removeAt(row);
                endRemoveRows();
                return true;
            }
            */


bool DefaultApplications::running()
{
    return m_running;
}


void DefaultApplications::setRunning(const bool &running)
{
    if(m_running !=running){
        m_running = running;
        emit runningChanged();
    }
}

void DefaultApplications::changeData(int index, QString appConfig, QString path, QString icon)
{

    defAppsThread.changeData(index,appConfig,path,icon);
}

void DefaultApplications::remove(int index)
{
    defAppsThread.removeItem(index);
}

void DefaultApplications::addItem(QString groupName,QString mimetype)
{
    defAppsThread.addItem(groupName,mimetype);
}

bool DefaultApplications::extended()
{
    return m_extended;
}


void DefaultApplications::setExtended(const bool &extended)
{
    if(defAppList == NULL) return;
    //if(m_extended == extended) return;

    m_extended = extended;
    //emit extendedChanged();


    connect(&defAppsThread,&DefaultApplicationsThread::running,this,&DefaultApplications::setRunning);
    connect(&defAppsThread,&DefaultApplicationsThread::beginReset,this,[=](){
        beginResetModel();
    });
    connect(&defAppsThread,&DefaultApplicationsThread::endReset,this,[=](){
        endResetModel();
    });
    connect(&defAppsThread,&DefaultApplicationsThread::dataChanged,this,[=](int index){
        QModelIndex item =createIndex(index,index);
        emit dataChanged(item, item, {Name,Icon,Path});

    });
    connect(&defAppsThread,&DefaultApplicationsThread::preItemRemoved,this,[=](int index){
         beginRemoveRows(QModelIndex(),index,index);

    });
    connect(&defAppsThread,&DefaultApplicationsThread::postItemRemoved,this,[=](){

        endRemoveRows();
    });
    connect(&defAppsThread,&DefaultApplicationsThread::preItemAdded,this,[=](int size){
         beginInsertRows(QModelIndex(),size,size);

    });
    connect(&defAppsThread,&DefaultApplicationsThread::postItemAdded,this,[=](){

        endInsertRows();
    });
    defAppsThread.setLanguage(m_language);
    defAppsThread.reset(extended);

}

/*
            bool DefaultApplications::dublicate(QString app)
            {
                QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS", "ExtendedDefaultApps");
                settings.setIniCodec("UTF-8");
                QStringList groupNameSplit =app.split(" ");

                return settings.childGroups().contains(groupNameSplit.at(0));

            }

            void DefaultApplications::saveToSettings(int index)
            {
                QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS", m_extended ?"ExtendedDefaultApps":"DefaultApps");
                settings.setIniCodec("UTF-8");
                DefaultApps app =defAppList.at(index);
             settings.beginGroup(app.category);
             settings.setValue("name",app.name);
             settings.setValue("icon",app.icon);
            settings.setValue("path",app.path);
            settings.setValue("config",app.config);

            if(m_extended) settings.setValue("mimetype",app.mimetypeName);


           // if(m_extended&&app.name.compare("")==0){
                //removeRows(index,1);
                //settings.remove("");
            //}
            settings.endGroup();

            }

            void DefaultApplications::add(QString name)
            {

            if(dublicate(name)) return;

            m_name=name;
            insertRow(defAppList.size());
            }


            void DefaultApplications::remove(int index)
            {
                QSettings settings(QSettings::NativeFormat,QSettings::UserScope,"KOS", "ExtendedDefaultApps");
                settings.setIniCodec("UTF-8");
                settings.remove(defAppList.at(index).category);
                removeRows(index,1);
            }
*/
QHash<int, QByteArray> DefaultApplications::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Icon] = "defAppIcon";
    roles[Path] = "defAppPath";
    roles[Category] = "category";
    roles[Mimetype] = "mimetype";
    roles[Suffix] = "suffix";
    roles[Config] = "config";


    return roles;
}

QString DefaultApplications::language()
{
    return m_language;
}

void DefaultApplications::setLanguage(const QString &language)
{
    if(m_language!=language){
        m_language=language;
        emit languageChanged();

    }
}
