#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>

#include <QIcon>
#include <QDebug>
#include <QImage>

class ImageProvider : public QQuickImageProvider {



public:
    ImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Pixmap) {


    }



    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {



        QIcon icon = QIcon::fromTheme(id);


        //QPixmap pixmap;

        if (requestedSize.isValid())
            return icon.pixmap(requestedSize);



        return icon.pixmap(128,128);
    }


};

#endif // IMAGEPROVIDER_H
