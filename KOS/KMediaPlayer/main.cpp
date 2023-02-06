#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>


#include "stylemanager.h"
#include "imageprovider.h"
#include "windowmanager.h"
#include "internalmusic.h"
#include "usbmodel.h"
#include "bluetoothdevicemodel.h"
#include "bluetoothdevice.h"
#include "language.h"

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



    app.setOrganizationName("KOS");
    app.setOrganizationDomain("com.kos");
    app.setApplicationName("AudioPlayer");
    engine.addImageProvider("icons", new ImageProvider());
    qmlRegisterType<WindowManager>("WindowManager",1,0,"WindowManager");
    qmlRegisterType<UsbModel>("UsbModel",1,0,"UsbModel");
    qmlRegisterType<InternalMusic>("InternalAudioModel",1,0,"InternalAudioModel");
    qmlRegisterType<BluetoothDeviceModel>("BluetoothDeviceModel",1,0,"BluetoothDeviceModel");
    qmlRegisterType<BluetoothDevice>("BluetoothDevice",1,0,"BluetoothDevice");



    if(argc > 0){

        engine.rootContext()->setContextProperty("musicFile",argv[1]);
    }else{
        engine.rootContext()->setContextProperty("musicFile","");
    }


    //load style
    StyleManager style;
    engine.rootContext()->setContextProperty("style", &style);
    engine.rootContext()->setContextProperty("themeData", &style.data);

    Language lang(&engine);
    lang.init();
    //engine.rootContext()->setContextProperty("lang", &lang);

    engine.load(url);

    return app.exec();
}
