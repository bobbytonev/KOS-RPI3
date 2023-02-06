#include "fontsmodel.h"

FontsModel::FontsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int FontsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return fontsCount;
}

QVariant FontsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case FontFamily:
        return QVariant(fonts.at(index.row())).toString();
        break;
    default:
        return QVariant();

    }
    return QVariant();
}
QHash<int, QByteArray> FontsModel::roleNames() const
{

    QHash<int, QByteArray> roles;
    roles[FontFamily] = "fontFamily";

    return roles;
}

void FontsModel::init()
{
    QFontDatabase fd;
    fonts = fd.families();
    fontsSize = fonts.size();

}

bool FontsModel::active() const
{
    return m_active;
}

void FontsModel::setActive(const bool &active)
{
    if(m_active == active) return;

    m_active = active;
    emit activeChanged();


    if(active) init();

}
bool FontsModel::canFetchMore(const QModelIndex &parent) const
{

    if(parent.isValid())
        return false;
    return fontsCount < fontsSize;
}

void FontsModel::fetchMore(const QModelIndex &parent)
{
    if(parent.isValid())
        return;

    const int start = fontsCount;
    const int reminder = fontsSize - start;
    const int itemToFetch = qMin(buffer,reminder);

    if(itemToFetch <=0)
        return;

    beginInsertColumns(QModelIndex(),start,start+itemToFetch-1);
    fontsCount+=itemToFetch;
    endInsertRows();

}

