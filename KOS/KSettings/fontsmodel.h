#ifndef FONTSMODEL_H
#define FONTSMODEL_H

#include <QAbstractListModel>
#include <QFontDatabase>
#include <QDebug>

class FontsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
public:
    enum {
        FontFamily
    };
    explicit FontsModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void init();

    bool active() const;
    void setActive(const bool& active);


protected:
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

signals:
    void activeChanged();

private:
    QStringList fonts;
    int fontsCount = 0;
    int fontsSize;
    const int buffer = 15;
    bool m_active=false;
};

#endif // FONTSMODEL_H
