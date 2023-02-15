import QtQuick 2.12
import WifiService 1.0
import QtQuick.Controls 2.15
Button {
    id:control
    property bool connected: wifiService.state == "online" ||  wifiService.state == "ready"

    property bool connecting: wifiService.state == "configuration" ||  wifiService.state == "association"

    property bool idle: wifiService.state == "failure"
                        ||  wifiService.state == "idle" ||  wifiService.state == "disconnect"


    signal disconnect();
    onDisconnect: {
        wifiService.disconnect()
    }

    onIdleChanged: {
        if(idle) frame.opacity = 0
    }


    Frame{
        id:frame
        anchors.fill: parent
        enabled:false
        opacity:0
    }
    SequentialAnimation{
        running:connecting
        loops: Animation.Infinite
        NumberAnimation{
            target:frame
            property: "opacity"
            to:1
            from:0
            duration:200
        }
        NumberAnimation{
            target:frame
            property: "opacity"
            to:0
            from:1
            duration:200
        }
    }







    WifiService{
        id:wifiService

        //wifiPath: servicePath

        Component.onCompleted: {

            state = serviceState;
            name =serviceName;
            strength = serviceStrength
            security = serviceSecurity
            wifiPath = servicePath

        }

    }
    Image{
        anchors.right: parent.right
        width:parent.height/3
        height:width
        cache:false
        anchors.rightMargin: width
        anchors.verticalCenter: parent.verticalCenter
        visible:wifiService.security == "psk"
        source:!style.icon_pack_reset ? "image://icons/wireless-password" : ""
    }

    onClicked: {
        if(!connected)
            wifiService.makeConnection()
        else{

            infoDiatlog.buttonIndex = index;
            infoDiatlog.open();
        }


    }

    onPressAndHold: {
        wifiService.remove()
        //informationDialog.open()
    }


    highlighted: connected
    height:window.height*0.12
    text:wifiService.name +( connecting ? qsTr("\tConnecting...") : connected ? qsTr("\tConnected"):"")
    icon.source:{

        if(!style.icon_pack_reset){
            var strenght=0;
            if(wifiService.strength < 25 ){
                strenght=25;
            }else if(wifiService.strength > 25 && wifiService.strength < 50){
                strenght=50;
            }else if(wifiService.strength > 50 && wifiService.strength < 75 ){

                strenght=75;
            }else if(wifiService.strength> 75){
                strenght=100;

            }
            return "image://icons/network-wireless-"+strenght;
        }
        return "";
    }


}

