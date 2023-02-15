
#include "trayiconlist.h"

TrayIconList::TrayIconList()
{


    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus SYSTEM bus.");
        return;
    }



    session.connect("", "/TrayIcons", "com.kos.environment", "showTrayIcon", this, SLOT(showTrayIcon(QString,int,QString,QString)));
    session.connect("", "/TrayIcons", "com.kos.environment", "showCustomTrayIcon", this, SLOT(showCustomTrayIcon(QString,int,QString)));

    session.connect("", "/TrayIcons", "com.kos.environment", "close", this, SLOT(close(QString,int)));

    session.connect("", "/TrayIcons", "com.kos.environment", "running", this, SLOT(running()));

    session.connect("", "/TrayIcons", "com.kos.environment", "changeIcon", this, SLOT(changeIcon(QString,int,QString)));



    if(!session.registerObject("/TrayIcons", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject - TrayIcons.");
        return;
    }

    if(!session.registerService("com.kos.environment")) {
        qFatal("Cannot registerService - TrayIcons.");
        return;
    }




}

int TrayIconList::dublicate(QString appName, int trayId)
{
    int index = -1;

    for(int i=0;i < trayIcons.size();i++){
        TrayIconItem item = trayIcons.at(i);
        if(item.appName.compare(appName) == 0 && item.trayId/1000 == trayId/1000){
            index = i;
            break;
        }

    }

    return index;


}

QVector<TrayIconItem> TrayIconList::items()
{
    return trayIcons;
}

bool TrayIconList::setItemAt(int index, const TrayIconItem &item)
{
    if(index < 0 || index >= trayIcons.size())
        return false;


    const TrayIconItem &oldItem = trayIcons.at(index);
    if(oldItem.trayId==item.trayId&&oldItem.text == item.text && oldItem.imagePath == item.imagePath && oldItem.menus == item.menus)
        return false;

    trayIcons[index] = item;
    return true;
}

bool TrayIconList::sendSignal(QString signalName,QString appName,int trayId)
{
    QStringList splitList = appName.split(".");
   int newTrayId =trayId/1000;
    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/TrayIcons","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(newTrayId));
    return session.send(m);

}

bool TrayIconList::sendContextMenuSignal(int index, QString signalName, QString appName, int trayId)
{
    QStringList splitList = appName.split(".");
    trayId =trayId/1000;
    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/TrayIcons","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(trayId));
    QList<QVariant> args;
    args.append(index);
    m.setArguments(args);
    return session.send(m);
}

void TrayIconList::setRunning(bool running)
{
    if(m_running != running){
        m_running = running;
        QDBusMessage m =QDBusMessage::createSignal("/TrayIcons","com.kos.environment","runningChanged");
        session.send(m);

    }
}






void TrayIconList::showTrayIcon(QString appName, int trayId, QString imagePath, QString text, QStringList menus)
{


    int index =dublicate(appName,  trayId);

    TrayIconItem item;
    item.appName=appName;
    item.trayId=trayId;
    item.imagePath=imagePath;
    item.imageProvider = !imagePath.startsWith("file:///");
    item.text=text;
    item.menus=menus;

    if(index > -1){

        if(setItemAt(index,item)){
            emit trayIconChanged(index);
        }
    }else{

        emit preTrayIconAppended();
        trayIcons.append(item);
        emit postTrayIconAppended();

    }

}

void TrayIconList::showCustomTrayIcon(QString appName, int trayId, QString qmlFilePath)
{
    //emit preCustomTrayIconAppended();

    TrayIconItem item;
    item.appName=appName;
    item.trayId=trayId;
    item.qmlPath=qmlFilePath;

    emit preTrayIconAppended();
    trayIcons.append(item);
    emit postTrayIconAppended();
    //emit postCustomTrayIconAppended();
}

int TrayIconList::close(QString appName, int trayId)
{
    int index = dublicate( appName,  trayId);

    if(index > -1 ){
        emit preTrayIconRemoved(index);
        trayIcons.remove(index);
        emit postTrayIconRemoved();
    }
    return index;
}

bool TrayIconList::running()
{
    return m_running;
}

void TrayIconList::changeIcon(QString appName, int trayId, QString imagePath)
{
    int index = dublicate(appName,trayId);

    if(index > -1){
        TrayIconItem item = trayIcons.at(index);
        item.imagePath = imagePath;
        trayIcons[index] =item;
        emit iconChanged(index);
    }

}


/*
#include "trayiconlist.h"
#include <QtConcurrent>

TrayIconList::TrayIconList()
{


    int listSize = size();
    for(int i=0;i<listSize;i++){
        QString objectPath = get(i);

        TrayIcon* trayIcon =new TrayIcon();
        trayIcon->setIndex(trayIcons.size());
        trayIcon->setObjectPath(objectPath);
        trayIcons.insert(objectPath,trayIcon);
        connectSignals(trayIcon);
    }
    QDBusConnection::systemBus().connect("",  "/com/kos/trays","com.kos.environment", "trayAdded", this, SLOT(trayAdded(QString)));
    QDBusConnection::systemBus().connect("",  "/com/kos/trays","com.kos.environment", "trayRemoved", this, SLOT(trayAdded(int)));

}

TrayIconList::~TrayIconList()
{
    qDeleteAll(trayIcons);
}

QMap<QString, TrayIcon *> TrayIconList::items()
{
    return trayIcons;
}


bool TrayIconList::sendSignal(QString signalName,QString appName,int trayId)
{
    QStringList splitList = appName.split(".");
    int newTrayId =trayId/1000;
    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/TrayIcons","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(newTrayId));
    return session.send(m);

}

bool TrayIconList::sendContextMenuSignal(int index, QString signalName, QString appName, int trayId)
{
    QStringList splitList = appName.split(".");
    trayId =trayId/1000;
    if(splitList.size() < 2) return false;

    QDBusMessage m =QDBusMessage::createSignal("/TrayIcons","com.kos.environment",splitList.at(1)+splitList.last()+signalName+QString::number(trayId));
    QList<QVariant> args;
    args.append(index);
    m.setArguments(args);
    return session.send(m);
}

QString TrayIconList::get(int index)
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/com/kos/trays","","get");
    QList<QVariant> args;
    args<<index;
    m.setArguments(args);
    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toString();
    }
    return "";
}
int TrayIconList::size()
{
    QDBusMessage m = QDBusMessage::createMethodCall("com.kos.environment","/com/kos/trays","","size");

    QDBusMessage response = QDBusConnection::systemBus().call(m);


    QList<QVariant> list =response.arguments();
    if(!list.isEmpty()){
        return list.at(0).toInt();
    }
    return -1;
}

void TrayIconList::connectSignals(TrayIcon *icon)
{
    connect(icon,SIGNAL(trayIdChanged(int)),this,SLOT(trayId(int)),Qt::DirectConnection);
    connect(icon,SIGNAL(textChanged(int)),this,SLOT(text(int)),Qt::DirectConnection);
    connect(icon,SIGNAL(imagePathChanged(int)),this,SLOT(imagePath(int)));
    connect(icon,SIGNAL(menusChanged(int)),this,SLOT(menus(int)));
}

void TrayIconList::disconnectSignals(TrayIcon *icon)
{
    disconnect(icon,SIGNAL(trayIdChanged(int)),this,SLOT(trayId(int)));
    disconnect(icon,SIGNAL(textChanged(int)),this,SLOT(text(int)));
    disconnect(icon,SIGNAL(imagePathChanged(int)),this,SLOT(imagePath(int)));
    disconnect(icon,SIGNAL(menusChanged(int)),this,SLOT(menus(int)));
}

void TrayIconList::trayAdded(QString path)
{

    emit preTrayIconAppended();
    QString objectPath =path;

    TrayIcon* trayIcon =new TrayIcon();
    trayIcon->setIndex(trayIcons.size());
    trayIcon->setObjectPath(objectPath);
    trayIcons.insert(objectPath,trayIcon);
    connectSignals(trayIcon);
    emit postTrayIconAppended();

}

void TrayIconList::trayRemoved(int index)
{
    emit preTrayIconRemoved(index);
    QString key = trayIcons.keys().at(index);
    disconnectSignals(trayIcons.values().at(index));
    delete [] trayIcons.value(key);
    if(trayIcons.value(key) == NULL) qDebug()<<"EVERYTHING IS OKEY TRAY IS NULL....";
    for(int i=index+1 ;i<trayIcons.size();i++){
        trayIcons.values().at(i)->setIndex(trayIcons.values().at(i)->index()-1);
    }

    trayIcons.remove(key);
    emit postTrayIconRemoved();
}

void TrayIconList::trayId(int index)
{
    emit trayIdChanged(index);
}

void TrayIconList::imagePath(int index)
{
    emit imagePathChanged(index);
}

void TrayIconList::text(int index)
{
    emit textChanged(index);
}

void TrayIconList::menus(int index)
{
    emit menusChanged(index);
}
*/









