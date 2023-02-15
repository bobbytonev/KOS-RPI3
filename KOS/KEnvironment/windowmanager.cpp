#include "windowmanager.h"

WindowManager::WindowManager()
{
    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus SYSTEM bus.-WindowManager");
        return;
    }


    session.connect("", "/Windows", "com.kos.environment", "showFullScreen", this, SLOT(showFullScreen(int)));
    session.connect("", "/Windows", "com.kos.environment", "showMaximized", this, SLOT(showMaximized(int)));
    session.connect("", "/Windows", "com.kos.environment", "showMinimized", this, SLOT(showMinimized(int)));


   if(!session.registerObject("/Windows", this, QDBusConnection::ExportScriptableContents)) {

         qFatal("Cannot registerObject.-WindowManager");
        return;
    }

    if(!session.registerService("com.kos.environment")) {

       qFatal("Cannot registerService-WindowManager.");

        return;
    }
}

void WindowManager::homeClicked()
{
    QDBusMessage m =QDBusMessage::createSignal("/Windows","com.kos.environment","homeClicked");
    session.send(m);
}

void WindowManager::back(int pid)
{

    QDBusMessage m =QDBusMessage::createSignal("/Windows","com.kos.environment","Back"+QString::number(pid));
    session.send(m);
}

void WindowManager::changeState(int state,int pid)
{

    QDBusMessage m =QDBusMessage::createSignal("/Windows","com.kos.environment","StateChanged"+QString::number(pid));
    QList<QVariant> args;
    args << state;
    m.setArguments(args);
    session.send(m);

}

void WindowManager::showFullScreen(int pid)
{
    emit fullScreen(pid);
}

void WindowManager::showMaximized(int pid)
{
    emit maximized(pid);
}

void WindowManager::showMinimized(int pid)
{
    emit minimized(pid);
}
