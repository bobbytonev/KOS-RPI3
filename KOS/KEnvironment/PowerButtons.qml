//import QtQuick 2.0
//Item{}

import QtQuick 2.0
import QtQuick.Controls 2.15
import PowerManager 1.0
Item {
    id:item
    width:parent.width
    height:window.height*0.09
    property int index:0

    PowerManager{
        id:power
    }
    BusyIndicator{
        anchors.centerIn: parent
        width:window.height*0.05
        height:width
        running:index === -1
    }

    Timer{
        running:index > 0
        interval:2000
        onTriggered: {

            index = 0
        }
    }


    Row{
        anchors.centerIn: parent



        Button{
            id:systemShutdown
            width:item.height
            height:width;
            visible:index !==2&&index >= 0
            display:Button.IconOnly
            icon.source:!style.icon_pack_reset ? "image://icons/system-shutdown" : ""
            scale:index == 1  ? 1.2 :1
            onClicked: {
                if(index !==1)
                index = 1
                else{power.shutdown();index=-1}
            }

            Behavior on scale{
                NumberAnimation{duration:400;easing.type: Easing.InOutQuad}
            }


        }
        Button{
            id:systemReboot
            width:window.height*0.09
            height:width;
            display:Button.IconOnly
            visible:index !==1&&index >= 0
            scale:index == 2  ? 1.2 :1
            icon.source:!style.icon_pack_reset ? "image://icons/system-reboot" : ""



            onClicked: {
                if(index !==2)
                index = 2
                else{power.reboot();index=-1}

            }

            Behavior on scale{
                NumberAnimation{duration:400;easing.type: Easing.InOutQuad}
            }




        }



    }
}

