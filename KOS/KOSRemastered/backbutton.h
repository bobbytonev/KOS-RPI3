#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include <QObject>
#include <QQmlApplicationEngine>

class BackButton : public QObject
{
    Q_OBJECT
public:
    BackButton(QQmlApplicationEngine* engine);
   Q_INVOKABLE void fire(QObject* window);

private:
    QQmlApplicationEngine* m_engine;
};

#endif // BACKBUTTON_H
