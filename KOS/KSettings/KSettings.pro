QT +=core quick quickcontrols2 dbus virtualkeyboard
CONFIG+=qtquickcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        appinfo.cpp \
        applications.cpp \
        applicationsthread.cpp \
        bluetoothdevice.cpp \
        bluetoothdevicemodel.cpp \
        bluetoothmanager.cpp \
        defaultapplications.cpp \
        defaultapplicationsthread.cpp \
        fontsmodel.cpp \
        hwclock.cpp \
        imageprovider.cpp \
        language.cpp \
        languagechooser.cpp \
        main.cpp \
        mimetypes.cpp \
        stylemanager.cpp \
        timezonemodel.cpp \
        volumecontrol.cpp \
        wifi.cpp \
        wifimodel.cpp \
        wifiservice.cpp \
        windowmanager.cpp

RESOURCES += qml.qrc


TRANSLATIONS = bg_Bg.ts \
                fr_Fr.ts \
                 de_De.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    NetworkManager.h \
    SystemInformation.h \
    appinfo.h \
    applications.h \
    applicationsthread.h \
    bluetoothdevice.h \
    bluetoothdevicemodel.h \
    bluetoothmanager.h \
    defaultapplications.h \
    defaultapplicationsthread.h \
    fontsmodel.h \
    hwclock.h \
    imageprovider.h \
    language.h \
    languagechooser.h \
    mimetypes.h \
    mimetypethread.h \
    process.h \
    stylemanager.h \
    timezonemodel.h \
    volumecontrol.h \
    wifi.h \
    wifimodel.h \
    wifiservice.h \
    windowmanager.h

