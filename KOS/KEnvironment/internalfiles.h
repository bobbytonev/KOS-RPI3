#ifndef INTERNALMUSIC_H
#define INTERNALMUSIC_H

#include <QAbstractListModel>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>

class InternalFiles : public QAbstractListModel
{
    Q_OBJECT



public:
    enum {
        FileUrl = Qt::UserRole,
        FileName

    };
    explicit InternalFiles(QObject *parent = nullptr);



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void activate();
    QString getFileName(QString path);
    QString get(int index) const;
    int size() const;
protected:
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
public slots:
    void fileRemoved(int index,QString path);
    void fileAdded(QString path);
    void fileRenamed(int index,QString oldPath,QString newPath);

private:
    //QList<AudioItem> audioList;
    const QString FILE_TYPE = "/Image";
    int imageCount = 0;
    int imagesSize;
    int buffer=5;

};

#endif // INTERNALMUSIC_H
