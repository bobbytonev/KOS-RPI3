#include "windowmanager.h"

WindowManager::WindowManager()
{


    //QDBusConnection conn=  QDBusConnection::connectToBus(QDBusConnection::SessionBus,"com.kos.environment");
    system.connect("", "/Windows", "com.kos.environment","Back"+
                 QString::number(WINDOW_PID),this,SLOT(backButton()));

    system.connect("", "/Windows", "com.kos.environment","StateChanged"+
                 QString::number(WINDOW_PID),this,SLOT(changeState(int)));
}

void WindowManager::requestFullScreen()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/Windows", "", "showFullScreen");
    QList<QVariant> args;
    args << WINDOW_PID;
    m.setArguments(args);
    system.asyncCall(m);
}



void WindowManager::requestMaximized()
{

    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/Windows", "", "showMaximized");
    QList<QVariant> args;
    args << WINDOW_PID;
    m.setArguments(args);
    system.asyncCall(m);
}

void WindowManager::requestMinimized()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/Windows", "", "showMinimized");
    QList<QVariant> args;
    args << WINDOW_PID;
    system.asyncCall(m);

}

void WindowManager::backButton()
{

    emit backClicked();
}

void WindowManager::changeState(int state)
{

    emit stateChanged(state);
}

