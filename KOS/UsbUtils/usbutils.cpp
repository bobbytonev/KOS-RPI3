#include "usbutils.h"
#include <errno.h>
#include <QProcess>
usbutils::usbutils()
{

    //icon.setMap(&usbList);
    //dbus.setUsbList(&usbList);
    //connect(this,SIGNAL(sizeChanged(int)),&icon,SLOT(sizeUpdated(int)));

    lang.init();

    QDBusConnection conn =QDBusConnection::systemBus();
    conn.connect("", "/TrayIcons", "com.kos.environment","kosusbtrayiconMClicked56",this,SLOT(menuClicked(int)));



    //connect(this,SIGNAL(emitDbusSignal(QString,QList<QVariant>)),&dbus,SLOT(sendSingnal(QString,QList<QVariant>)));
    //mountOnBoot();
    //start();
    QDBusMessage message =QDBusMessage::createMethodCall("com.kos.environment","/TrayIcons",
                                                         "","running");
    QList<QVariant> arguments;
    QDBusMessage returnVar =QDBusConnection::systemBus().call(message);
    QList<QVariant> list  =returnVar.arguments();
    if(returnVar.errorName().isEmpty()){
        if(list.first().toBool())
            init();

    }else{
        conn.connect("", "/TrayIcons", "com.kos.environment","runningChanged",this,SLOT(init()));

    }
}

void usbutils::run()
{

    struct udev *udev;
    struct udev_device *dev;
    struct udev_monitor *mon;


    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        return ;
    }


    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);


    while (1) {
        this->msleep(50);

        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        ret = select(fd+1, &fds, NULL, NULL, &tv);


        if (ret > 0 && FD_ISSET(fd, &fds)) {
            //


            dev = udev_monitor_receive_device(mon);
            if (dev) {

                if(strcmp(udev_device_get_devtype(dev),"partition")==0){

                    if(strcmp(udev_device_get_action(dev),"add")==0){


                        QString partition = udev_device_get_devnode(dev);

                        add(partition,false);



                    }else if(strcmp(udev_device_get_action(dev),"remove")==0){


                        eject(udev_device_get_devnode(dev));
                        // emit deviceRemoved(QDir::homePath()+"/usb",udev_device_get_devnode(dev));



                    }


                    udev_device_unref(dev);
                }
            }
            else {
                printf("No Device from receive_device(). An error occured.\n");
            }
        }

    }




}

void usbutils::mountOnBoot()
{
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;


    udev = udev_new();
    if (!udev) {
        printf("Can't create udev\n");
        exit(1);
    }


    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path;


        path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);


        const char * nodePath = udev_device_get_devnode(dev);






        dev = udev_device_get_parent_with_subsystem_devtype(
                    dev,
                    "usb",
                    "usb_device");
        if (!dev) {
            printf("Unable to find parent usb device.");
            break;
        }
        int len =strlen(nodePath);
        if(isdigit(nodePath[len-1])){

            add(nodePath,true);
            // qDebug()<<udev_device_get_sysattr_value(dev,"product");
            //deviceName = nodePath;
            //device=true;

            //break;
        }




        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);

    udev_unref(udev);

}

void usbutils::add(QString partition,bool firstTime)
{
    QString moutingPoint =createMoutingPoint(partition);
    if(moutingPoint.isEmpty()) return;


    char options[] = "uid=1000,gid=1000";

    int  error = mount(partition.toStdString().c_str(),
                       moutingPoint.toStdString().c_str(),"vfat",0,options);


    if(error == 0 || firstTime == true){
        QString deviceName = getDeviceName(partition);
        QStringList list{moutingPoint,deviceName};
        usbList.insert(partition,list);

        QList<QVariant> arrgs;
        arrgs.append(usbList.value(partition));
        emit emitDbusSignal("partitionInserted",arrgs);
        emit sizeChanged(usbList.size());


    }
}

void usbutils::eject(QString partition)
{

    QStringList list =usbList.value(partition);
    if(list.isEmpty())return;

    QString moutingPoint = list.at(0);

    int error = umount2(moutingPoint.toStdString().c_str(),MNT_FORCE);

    QList<QVariant> arrgs;
    arrgs.append(usbList.value(partition));
    usbList.remove(partition);
    emit emitDbusSignal("partitionRemoved",arrgs);
    emit sizeChanged(usbList.size());


}

QString usbutils::createMoutingPoint(QString partition)
{
    // partition = /dev/sdb1
    QStringList list = partition.split("/");

    if(list.isEmpty()) return "";


    QString moutingPoint = "/media/usbs/"+list.last();

    QDir dir(moutingPoint);

    if(!dir.exists()){
        if(!dir.mkpath(".")) return "";
    }



    return moutingPoint;
}

void usbutils::registerDBus()
{
    if (!session.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return;
    }


    session.connect("", "/", "com.kos.usbmanager", "get", this, SLOT(get(QStringList)));
    session.connect("", "/", "com.kos.usbmanager", "size", this, SLOT(size(int)));

    if(!session.registerObject("/", this, QDBusConnection::ExportScriptableContents)) {
        qFatal("Cannot registerObject.");
        return;
    }

    if(!session.registerService("com.kos.usbmanager")) {
        qFatal("Cannot registerService.");
        return;
    }
}

QMap<QString, QStringList> usbutils::getUsbList()
{
    return usbList;
}

QString usbutils::getDeviceName(QString partition)
{
    BootSector bootSector;
    FILE* partitionRead = NULL;
    if((partitionRead = fopen(partition.toStdString().c_str(),"rb")) == NULL) return "";

    //formula
    //11 - number of butes per sector //2 bytes
    //13 - number of sectors per cluster //1 bytes
    //14 - reserved sectors //2 bytes
    //16 - number of FATs //1 byte
    //36 - number of sectors per FAT //4
    //44 - number of root cluster //4
    long rootDirectoryPosition=0 ;
    fseek(partitionRead,11,SEEK_SET);
    fread(&bootSector.bytesPerSector,sizeof(short),1,partitionRead);
    fread(&bootSector.numberOfSectorsPerCluster,sizeof(char),1,partitionRead);
    fread(&bootSector.reservedSectors,sizeof(short),1,partitionRead);
    fread(&bootSector.numberOfFATs,sizeof(char),1,partitionRead);

    fseek(partitionRead,36,SEEK_SET);
    fread(&bootSector.numberOfSectorsPerFat,sizeof(int),1,partitionRead);
    fseek(partitionRead,44,SEEK_SET);
    fread(&bootSector.numberOfRootCluster,sizeof(int),1,partitionRead);

    rootDirectoryPosition =(bootSector.bytesPerSector * bootSector.reservedSectors)
            + (bootSector.numberOfSectorsPerFat * bootSector.bytesPerSector
               *  bootSector.numberOfFATs);
    if(bootSector.numberOfRootCluster != 8){
        int cluster =bootSector.numberOfRootCluster - 2;
        rootDirectoryPosition += bootSector.numberOfSectorsPerCluster * cluster * bootSector.bytesPerSector;
    }

    fseek(partitionRead,rootDirectoryPosition,SEEK_SET);
    char name [11];
    fread(&name,sizeof(name),1,partitionRead);
    fclose(partitionRead);
    //QString partitionName = buffer;
    QString partitionName = name;

    return partitionName;
}
int usbutils::size()
{
    return usbList.size();
}
void usbutils::menuClicked(int index){
    if(size()==1){
        switch (index) {
        case 0:
        {

            QStringList args{"-c","KFileManager"+ usbList.values().at(0).at(0)+ "-platform wayland","kos"}; // fix

            QProcess::startDetached("su",args);
        }
            break;
        case 1:
            eject(usbList.keys().at(0));

            break;
        }
    }else{
        if(index < 0 || index >= size()) return;
        QStringList args{"-c","KFileManager"+ usbList.values().at(index).at(0)+ "-platform wayland","kos"}; // fix

        QProcess::startDetached("su",args);
    }




}

void usbutils::init()
{
    if(this->isRunning())return;


    icon.setMap(&usbList);
    dbus.setUsbList(&usbList);
    connect(this,SIGNAL(sizeChanged(int)),&icon,SLOT(sizeUpdated(int)));
    connect(this,SIGNAL(emitDbusSignal(QString,QList<QVariant>)),&dbus,SLOT(sendSingnal(QString,QList<QVariant>)));
    connect(&lang,&Language::languageChanged,this,&usbutils::updateTrayIconLanguage);
    mountOnBoot();
    start();
}

void usbutils::updateTrayIconLanguage()
{
    if(usbList.size() < 2)
        icon.sizeUpdated(usbList.size());
}

