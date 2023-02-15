
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QtDebug>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QCoreApplication>

class WindowManager : public QObject
{
    Q_OBJECT
public:
    WindowManager();

    Q_INVOKABLE void requestFullScreen();
    Q_INVOKABLE void requestMaximized();
    Q_INVOKABLE void requestMinimized();
signals:
    void backClicked();
    void stateChanged(int state);

public slots:
    void backButton();
    void changeState(int state);
private:
    const int WINDOW_PID = (QCoreApplication::applicationPid()*10)+2;
    QDBusConnection system = QDBusConnection::systemBus();
};

#endif // WINDOWMANAGER_H

