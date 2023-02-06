import QtQuick 2.15
import QtGraphicalEffects 1.15
import Qt.labs.settings 1.1
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent

    property bool  fullScreenVariable:false
    property alias dropDownMenu: dropDownMenu
    property alias shortcuts: shortcuts
    property alias trayDropDown: trayDropDown
    property alias settings: settings
    property alias fastBlur: fastBlur


    Connections{
        target: window
        function onHomeScreenChanged(){
            window.backButton = !window.homeScreen;
            if(window.homeScreen) fullScreenVariable = false
        }
    }
    onFullScreenVariableChanged: {
        if(!fullScreenVariable){
            header.headerLayout.opacity = 1
        }
    }

    Settings {
        id:settings
        property alias source:image.source
        property alias backgroundFillMode:image.fillMode
        property alias backgroundHorizontalAlignment:image.horizontalAlignment
        property alias backgroundVerticalAlignment:image.verticalAlignment
        property real appsIconSize:0.19
        property bool iconText: true
        property bool blur:true
        property bool alwaysBlur: false



    }



    Image{

        id:image
        visible:!fastBlur.visible
        anchors.fill: parent
        source:"kdefaultbg.jpg"
        sourceSize.width: window.width
        sourceSize.height: window.height


    }
    FastBlur{
        id:fastBlur
        anchors.fill: image
        source:image
        // visible:settings.blur
        radius:!settings.blur ? 0:settings.alwaysBlur ? 64 : window.backButton||window.shellSurfaces.count > 0 ? 64: 0
        Behavior on radius {
            NumberAnimation{
                duration:150
                easing.type: Easing.InOutQuad
            }

        }

    }




    Shortcuts{
        id:shortcuts
        y:header.height
        width:parent.width
        height:parent.height-y


    }

    DropDownMenu{
        id:dropDownMenu
        y:header.height
        width:parent.width
        height:parent.height-y
    }
    TrayDropDown{
        id:trayDropDown
        y:header.height
        width:parent.width
        height:parent.height-y
    }


    Widgets{
        anchors.fill: parent
        id:widgtes
    }
    Header{
        id:header
        // visible:!fullScreenVariable
        width:parent.width
        height:50
    }



    NotificationPopup{
        x:parent.width/2 - width/2

    }
    AppDrawer{
        id:appDrawer
        width:parent.width
        height:window.height*0.15
        y:window.height-height

    }



}
