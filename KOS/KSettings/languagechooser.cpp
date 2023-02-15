#include "languagechooser.h"

LanguageChooser::LanguageChooser(QObject *parent)
    : QAbstractListModel(parent)
{

    //init();
}

int LanguageChooser::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return size(); //langList.size();
}

QVariant LanguageChooser::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //LanguageItem item = langList.at(index.row());
    QStringList item  =get(index.row());
    switch (role) {
    case Name:
        return QVariant(item.at(0)).toString();
    case Prefix:
        return QVariant(item.at(1)).toString();
    default:
        return QVariant();

    }


}
QHash<int, QByteArray> LanguageChooser::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Prefix] = "prefix";


    return roles;
}

void LanguageChooser::init()
{
    /*
    int listSize = size();
    for(int i=0;i<listSize;i++){
        QStringList language = get(i);
        if(language.size() > 0){

            LanguageItem item ;
            item.name=language.at(0);
            item.prefix=language.at(1);
            langList.append(item);
        }
    }
    */


}

QStringList LanguageChooser::get(int index) const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/Language","","languageAt");
    QList<QVariant> args;
    args.append(index);
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toStringList();
    }
    return QStringList{};
}

int LanguageChooser::size() const
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.stylemanager","/Language","","size");
    QDBusMessage response = QDBusConnection::systemBus().call(m);
    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){

        return list.at(0).toInt();
    }

    return -1;
}
