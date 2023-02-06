import QtQuick 2.0
import QtQuick.Controls 2.15
import UsbModel 1.0
Item{
    SwipeView {
        id: swipeView
        anchors.fill: parent
        anchors.topMargin: tabBar.height+20
        currentIndex: tabBar.currentIndex
        onCurrentIndexChanged: {



        }


        Item{
            BusyIndicator{
                visible:myVideo.status == Loader.Loading
                anchors.centerIn: parent
            }
            Loader{
                id:myVideo
                anchors.fill: parent
                source:"MyVideo.qml"
                active:true
                asynchronous: true



            }
        }
        Repeater{
            model:usbModel
            delegate:Loader{
                id:usbLoader
                property string usbMoutingPoint:moutingPoint

                active:true
                source:"Usb.qml"
                asynchronous: true


            }
        }
        SubtitleSettings{

        }
    }
    UsbModel{
        id:usbModel
    }


    TabBar {
        id: tabBar
        visible:swipeView.visible
        x:parent.width/2 - width/2
        spacing: 20
        width: parent.width
        position: TabBar.Header
        currentIndex: swipeView.currentIndex

        background: Rectangle{
            color:"transparent"
        }


        TabButton {
            text: qsTr("Video");
            visible:tabBar.count > 1
        }


        Repeater{
            model:usbModel
            delegate:TabButton {
                text:deviceName


            }
        }
        TabButton{
            text: qsTr("Subtitles");
        }



    }
}
