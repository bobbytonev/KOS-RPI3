import QtQuick 2.0
import WifiModel 1.0
import QtQuick.Controls 2.15
ListView {
    id:view
    //anchors.fill: parent
    model:WifiModel{id:wifiModel}
    spacing:15
    clip:true
    header:Item{

        width:parent.width
        height:window.height*0.12


        RoundButton{
            id:reloadButton
            width:parent.height
            height:parent.height

            anchors.right: parent.right
            icon.source:!style.icon_pack_reset ? "image://icons/reload":""

            onClicked: {
                if(wifiModel.state != "Scanning")
                    wifiModel.scan()
            }
        }
        SequentialAnimation{
            running:wifiModel.state == "Scanning"
            loops: Animation.Infinite
            NumberAnimation{
                target:reloadButton
                from:0
                to:180
                property: "rotation"
                duration:200
            }
            NumberAnimation{
                target:reloadButton
                from:180
                to:360
                property: "rotation"
                duration:200
            }
        }
    }


    add:Transition{
        NumberAnimation{duration:200;property:"scale";to:1;from:0}
    }
    remove:Transition{
        NumberAnimation{duration:200;property:"width";to:0;from:1}
    }
    move:Transition{
        NumberAnimation{duration:200;property:"y";}
    }
    InformationDialog{
        id:infoDiatlog
        property int buttonIndex:-1
        text:qsTr("Disconnect from this network");
        onAccepted: {
            view.itemAtIndex(buttonIndex).disconnect()
        }

    }

    delegate:WifiButton{
        id:control
        width:view.width
        onClicked: {

        }

    }
}

