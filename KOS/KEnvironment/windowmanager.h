#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QDBusMessage>
#include <QDBusObjectPath>

class WindowManager : public QObject
{
    Q_OBJECT

public:
    WindowManager();




    Q_INVOKABLE void homeClicked();
    Q_INVOKABLE void back(int pid);
    Q_INVOKABLE void changeState(int state,int pid);
    //0 -widgetState
    //1 -normalState
    //2 -fullScreen
    //3 -minimized

signals:

    void fullScreen(int pid);
    void maximized(int pid);
    void minimized(int pid);
public slots:
    Q_SCRIPTABLE void showFullScreen(int pid);
    Q_SCRIPTABLE void showMaximized(int pid);
    Q_SCRIPTABLE void showMinimized(int pid);


private:
    //QDBusConnection session = QDBusConnection::sessionBus();
    QDBusConnection session = QDBusConnection::systemBus();

};

#endif // WINDOWMANAGER_H
