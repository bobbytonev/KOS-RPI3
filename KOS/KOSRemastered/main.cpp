#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <unistd.h>
#include <QSurfaceFormat>
#include <QUdpSocket>
#include <QStyleHints>

#include "stylemanager.h"
#include "applications.h"
#include "imageprovider.h"
#include "backbutton.h"
#include "volumecontrol.h"
#include "launcher.h"
#include "trayiconlist.h"
#include "trayiconmodel.h"
#include "notificationslist.h"
#include "notificationmodel.h"
#include "windowmanager.h"
#include "hwclock.h"
#include "internalfiles.h"
#include "language.h"

bool stopAnimation(){

    QUdpSocket socket;
    QByteArray Data;
    Data.append(1);
    return socket.writeDatagram(Data, QHostAddress::LocalHost, 7755);

}

int main(int argc, char *argv[])
{

    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

QGuiApplication::setSetuidAllowed(true);

    int result =0;
    bool firstRun=true;

    TrayIconList trayList;
    trayList.setRunning(true);
    NotificationsList notifyList;


    // QIcon::setFallbackThemeName("candy-icons");//fix me

    //setgid(1000);




    QGuiApplication app(argc, argv);
    QGuiApplication::styleHints()->setMousePressAndHoldInterval(500);
    do{


        if(!firstRun) qmlClearTypeRegistrations();


        //QSurfaceFormat format;
        // format.setSwapInterval(0);
        //QSurfaceFormat::setDefaultFormat(format);

        QQmlApplicationEngine engine;
        qmlRegisterType<WindowManager>("WindowManager",1,0,"WindowManager");
        setuid(1000);

        QStringList args{};
        QProcess::startDetached("KStarter",args);

        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

        engine.rootContext()->setContextProperty("stopAnimation", stopAnimation());

        engine.rootContext()->setContextProperty("_homeDir",QDir::homePath());
        engine.rootContext()->setContextProperty("trayList",&trayList);
        engine.rootContext()->setContextProperty("notifyList",&notifyList);


        app.setOrganizationName("KOS");
        app.setOrganizationDomain("kos.com");

        engine.addImageProvider("icons", new ImageProvider());

        qmlRegisterType<applications>("SystemApplications",1,0,"Applications");
        qmlRegisterType<InternalFiles>("ImageFiles",1,0,"ImageFiles");
        qmlRegisterType<HwClock>("SystemClock",1,0,"SystemClock");
        qmlRegisterType<VolumeControl>("VolumeControl",1,0,"VolumeControl");
        qmlRegisterType<TrayIconModel>("TrayIconModel",1,0,"TrayIconModel");
        qmlRegisterUncreatableType<TrayIconList>("TrayIcon",1,0,"TrayIconList", "TrayIconList should not be created in QML");
        qmlRegisterType<NotificationModel>("NotificationModel",1,0,"NotificationModel");
        qmlRegisterUncreatableType<NotificationsList>("Notifications",1,0,"NotificationsList", "NotificationList should not be created in QML");


        engine.rootContext()->setContextProperty("appLauncher", new Launcher(&engine));




        //load style
        StyleManager style;
        engine.rootContext()->setContextProperty("style", &style);
        engine.rootContext()->setContextProperty("themeData", &style.data);
        engine.addPluginPath("/usr/share/themes/"+style.styleName()+"/Launcher");
        app.setApplicationName(style.styleName());




        Language lang(&engine);
        lang.init("/usr/share/themes/"+style.styleName()+"/language/");
        engine.rootContext()->setContextProperty("lang", &lang);

        engine.load(url);

        result = app.exec();
        firstRun=false;

        notifyList.clearAll();


    }while(result==1337);



    return result;//app.exec();
}
