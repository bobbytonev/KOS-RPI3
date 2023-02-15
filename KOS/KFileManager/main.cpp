#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <unistd.h>

#include "stylemanager.h"
#include "imageprovider.h"
#include "windowmanager.h"
#include "internalfiles.h"
#include "usbmodel.h"
#include "launcher.h"
#include "kfilemanager.h"
#include "applications.h"
#include "language.h"


int main(int argc, char *argv[])
{



    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    int pid =(QCoreApplication::applicationPid()*10)+3;


    QByteArray array;
    array.setNum(pid);
    qputenv("QT_IVI_SURFACE_ID", array);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);



    app.setOrganizationName("KOS");
    app.setOrganizationDomain("com.kos");
    app.setApplicationName("FileManager");
    engine.addImageProvider("icons", new ImageProvider());
    qmlRegisterType<WindowManager>("WindowManager",1,0,"WindowManager");
    qmlRegisterType<UsbModel>("UsbModel",1,0,"UsbModel");
    qmlRegisterType<InternalFiles>("InternalFilesModel",1,0,"InternalFilesModel");
    qmlRegisterType<KFileManager>("KFileManager",1,0,"KFileManager");
    qmlRegisterType<applications>("AppStarter",1,0,"AppStarter");

    engine.rootContext()->setContextProperty("_homeDir",QDir::homePath());

    //load style
    StyleManager style;
    engine.rootContext()->setContextProperty("style", &style);
    engine.rootContext()->setContextProperty("themeData", &style.data);

    engine.rootContext()->setContextProperty("appLauncher", new Launcher(&engine));

    //load language
    Language lang(&engine);
    lang.init();
    //engine.rootContext()->setContextProperty("lang", &lang);

    if(argc > 0){

        engine.rootContext()->setContextProperty("folderPath",argv[1]);
    }else{
        engine.rootContext()->setContextProperty("folderPath","");
    }



    engine.load(url);

    return app.exec();
}
