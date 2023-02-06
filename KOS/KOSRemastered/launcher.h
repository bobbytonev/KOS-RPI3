#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QVariant>


class Launcher:public QProcess
{
    Q_OBJECT
public:
   Launcher(QObject *parent = nullptr);

   Q_INVOKABLE void start(const QString &program, const QVariantList &arguments={});
   Q_INVOKABLE QByteArray readAll();
};




#endif // LAUNCHER_H
