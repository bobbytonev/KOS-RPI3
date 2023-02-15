#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "volumecontrol.h"
#include "imageprovider.h"
#include "language.h"
#include "SystemInformation.h"
#include "defaultapplications.h"
#include "process.h"
#include "applications.h"
#include "mimetypes.h"
#include "hwclock.h"
#include "languagechooser.h"
#include "language.h"
#include "windowmanager.h"
#include "stylemanager.h"
#include "bluetoothmanager.h"
#include "bluetoothdevicemodel.h"
#include "bluetoothdevice.h"
#include "wifi.h"
#include "wifimodel.h"
#include "wifiservice.h"
#include "appinfo.h"
#include "timezonemodel.h"
#include "fontsmodel.h"


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


    engine.rootContext()->setContextProperty("_homeDir",QDir::homePath());


    qmlRegisterType<hwclock>("HwClock",1,0,"HardwareClock");
    qmlRegisterType<WindowManager>("WindowManager",1,0,"WindowManager");
    qmlRegisterType<VolumeControl>("VolumeControl",1,0,"VolumeControl");
    qmlRegisterType<applications>("AllApplications",1,0,"AllApplications");
    qmlRegisterType<DefaultApplications>("DefApps",1,0,"DefaultApplications");
    qmlRegisterType<mimetypes>("MimeTypes",1,0,"MimeTypes");
    qmlRegisterType<LanguageChooser>("Languages",1,0,"LanguageModel");
    qmlRegisterType<BluetoothManager>("BluetoothManager",1,0,"Bluetooth");
    qmlRegisterType<BluetoothDeviceModel>("BluetoothDeviceModel",1,0,"BluetoothDeviceModel");
    qmlRegisterType<BluetoothDevice>("BluetoothDevice",1,0,"BluetoothDevice");
    qmlRegisterType<Wifi>("Wifi",1,0,"Wifi");
    qmlRegisterType<WifiModel>("WifiModel",1,0,"WifiModel");
    qmlRegisterType<WifiService>("WifiService",1,0,"WifiService");
    qmlRegisterType<AppInfo>("ApplicationInfo",1,0,"ApplicationInfo");
    qmlRegisterType<TimezoneModel>("TimeZonesModel",1,0,"TimeZonesModel");
    qmlRegisterType<FontsModel>("FontsModel",1,0,"FontsModel");



    if(argc > 0){

        engine.rootContext()->setContextProperty("page",argv[1]);
    }else{
        engine.rootContext()->setContextProperty("page","");
    }




    //load style
    StyleManager style;
    engine.rootContext()->setContextProperty("style", &style);
    engine.rootContext()->setContextProperty("themeData", &style.data);
    engine.addPluginPath("/usr/share/themes/"+style.styleName()+"/Style");


    Language lang(&engine);
    lang.init();
    engine.rootContext()->setContextProperty("lang", &lang);


    app.setOrganizationName("KOS");
    app.setOrganizationDomain("com.kos");
    app.setApplicationName("settings");

    engine.addImageProvider("icons", new ImageProvider());



    SystemInformation info;
    engine.rootContext()->setContextProperty("info", &info);


    engine.load(url);




    return app.exec();
}
