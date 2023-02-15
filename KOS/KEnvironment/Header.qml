import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
Item{
    property bool flag: false
    property alias headerLayout: headerLayout
    SwipeView{
        id:swipe
        visible:headerLayout.opacity === 0
        orientation: Qt.Vertical
        width:parent.width
        height:15
        currentIndex:1


        Item{}
        Item{}
        Component.onCompleted: {
            swipe.contentItem.highlightMoveDuration = 0
        }

        onCurrentIndexChanged: {
            if(currentIndex === 0){
                headerLayout.opacity =1
                hideTimer.start()
            }

        }

    }


    Timer{
        id:hideTimer
        interval:3000
        running:fullScreenVariable&&!dropDownMenu.visible&&!trayDropDown.visible
        onTriggered: {
            swipe.currentIndex =1
            headerLayout.opacity = 0

        }

    }

    Row {
        id:headerLayout
        anchors.fill:parent
        enabled:opacity === 1
        //spacing:50
        //visible:!fullScreenVariable
        opacity:fullScreenVariable ? 0:1
        Behavior on opacity{
            NumberAnimation{
                duration:200
            }
        }


        Button{
            id:homeButton
            width:64
            height:48
            background:Shape {
                antialiasing: true
                vendorExtensionsEnabled: false
                smooth: true
                ShapePath {
                    strokeColor: "transparent"
                    fillColor: homeButton.down ?"#32000000":"#96000000"
                    startX: -40; startY:homeButton.height

                    PathLine { x: homeButton.width; y:  homeButton.height}
                    PathLine { x:homeButton.width+30; y:  0}
                    PathLine { x:0; y:  0}

                }
            }
            onClicked: {
                window.home();

            }


            Image{
                source: !style.icon_pack_reset ? "image://icons/go-home" : ""
                anchors.centerIn: parent
                width: parent.width/2.2
                height: width
                cache:false
            }
        }//homeButton

        NotificationArea{
            id:notifyArea
            width:window.width/4
            height:48

        }
        Item{width:50}
        Time{
            width:window.width-(homeButton.width*2+notifyArea.width*2+4*headerLayout.spacing)
            z:99
        }
        Item{width:50}
        TrayIconsArea{
            id:trayArea
            width:notifyArea.width
            height:48
        }


        Button{
            z:99999
            id:backButton
            focusPolicy: Qt.NoFocus
            scale:!window.homeScreen || window.backButton ? 1 : 0
            enabled: scale === 1
            width:homeButton.width
            height:homeButton.height

            Behavior on scale{
                NumberAnimation{
                    duration:200
                }
            }



            background:Shape {
                //id:back
                antialiasing: true
                //opacity:home.down ? 0.9:0.7
                vendorExtensionsEnabled: false
                smooth: true
                ShapePath {


                    strokeColor: "transparent"
                    fillColor: backButton.down ?"#32000000":"#96000000"
                    startX: backButton.width; startY:backButton.height

                    PathLine { x: 0; y:  backButton.height}
                    PathLine { x:-30; y:  0}
                    PathLine { x:backButton.width; y:  0}

                }
            }
            onClicked: {
                window.back();


            }


            Image{
                //image://icons/system-back
                source: !style.icon_pack_reset ? "image://icons/system-back" : ""
                anchors.centerIn: parent
                width: parent.width/2.2
                height: width
                cache: false
            }
        }

    }
}
