#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>


#include "stylemanager.h"
#include "imageprovider.h"
#include "windowmanager.h"
#include "internalfiles.h"
#include "usbmodel.h"

#include "srtparser.h"
#include "durationsave.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    int pid =(QCoreApplication::applicationPid()*10)+2;


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


    engine.rootContext()->setContextProperty("_homeDir",QDir::homePath());



    app.setOrganizationName("KOS");
    app.setOrganizationDomain("com.kos");
    app.setApplicationName("AudioPlayer");
    engine.addImageProvider("icons", new ImageProvider());
    qmlRegisterType<WindowManager>("WindowManager",1,0,"WindowManager");
    qmlRegisterType<UsbModel>("UsbModel",1,0,"UsbModel");
    qmlRegisterType<InternalFiles>("InternalVideoModel",1,0,"InternalVideoModel");
    qmlRegisterType<SrtParser>("Subtitles",1,0,"Subtitles");
    qmlRegisterType<DurationSave>("DurationSaver",1,0,"DurationSaver");


    if(argc > 0){

        engine.rootContext()->setContextProperty("videoFile",argv[1]);
    }else{
        engine.rootContext()->setContextProperty("videoFile","");
    }

    //load style
    StyleManager style;
    engine.rootContext()->setContextProperty("style", &style);
    engine.rootContext()->setContextProperty("themeData", &style.data);



    //exit(1);
    engine.load(url);

    return app.exec();
}
