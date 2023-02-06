#include <QCoreApplication>

#include "filecaching.h"
#include "cacheitem.h"
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    FileCaching file ;







    qDebug()<<QObject::connect(&app,SIGNAL(aboutToQuit()),&file,SLOT(updateSettings()));

    app.setOrganizationName("KOS");
    app.setOrganizationDomain("com.filecaching");
    app.setApplicationName("FileChache");

    int code = app.exec();
    file.updateSettings();
    qDebug()<<"UPDATE";
    return code;
    //return app.exec();
}
