#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H
#include <QIcon>
#include <QQuickImageProvider>

class ImageProvider:public QQuickImageProvider
{
public:
    explicit ImageProvider();
   Q_INVOKABLE QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // IMAGEPROVIDER_H
