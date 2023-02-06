QT += quick quickcontrols2 dbus network

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        applications.cpp \
        hwclock.cpp \
        internalfiles.cpp \
        language.cpp \
        launcher.cpp \
        main.cpp \
        notificationmodel.cpp \
        notificationslist.cpp \
        powermanager.cpp \
        stylemanager.cpp \
        trayicon.cpp \
        trayiconlist.cpp \
        trayiconmodel.cpp \
        volumecontrol.cpp \
        windowmanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    applications.h \
    hwclock.h \
    imageprovider.h \
    internalfiles.h \
    language.h \
    launcher.h \
    notificationmodel.h \
    notificationslist.h \
    powermanager.h \
    stylemanager.h \
    trayicon.h \
    trayiconlist.h \
    trayiconmodel.h \
    volumecontrol.h \
    windowmanager.h
