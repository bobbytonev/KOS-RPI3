#include "launcher.h"


Launcher::Launcher(QObject *parent)
    : QProcess(parent) {
}


void Launcher::start(const QString &program, const QVariantList &arguments) {
    QStringList args;

    Q_UNUSED(arguments);
    // qDebug() << "Running" << program;
    // convert QVariantList from QML to QStringList for QProcess

    // for (int i = 0; i < arguments.length(); i++)
    //       args<<arguments.at(i).toString();
    qputenv("WAYLAND_DISPLAY", QByteArray("wayland-2"));

    args << "-platform";
    args << "wayland-egl";


    QProcess::startDetached(program,args);
    // QProcess::start(program, args);

}

QByteArray Launcher::readAll() {
    return QProcess::readAll();
}
