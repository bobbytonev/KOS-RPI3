#ifndef LANGUAGECHOOSER_H
#define LANGUAGECHOOSER_H

#include <QAbstractListModel>
#include <QDebug>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>

class LanguageChooser : public QAbstractListModel
{
    Q_OBJECT


    struct LanguageItem
    {

        QString name,prefix;



    };
public:
    enum {
        Name = Qt::UserRole,
        Prefix
    };

    explicit LanguageChooser(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    void init();

    QStringList get(int index) const;
    int size() const;

private:
    //QVector<LanguageItem> langList;
    QDBusConnection session = QDBusConnection::systemBus();

};

#endif // LANGUAGECHOOSER_H
