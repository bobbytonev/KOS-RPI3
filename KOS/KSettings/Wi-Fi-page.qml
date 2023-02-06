import QtQuick 2.0
import QtQuick.Controls 2.15
import Wifi 1.0
Item {
    property bool load: false

    id:item
    signal scan();
    property alias textInput: textInput
    property alias wifi: wifi
    onVisibleChanged: {
        if(!visible&&textInput.visible){

            textInput.rejected()
            textInput.close()
        }
    }

    Wifi{
        id:wifi

        onCancel: {
            textInput.close()
        }
        onError:(error) => {
                    console.log(error);
                }
        onInputRequest: {
            textInput.open()
        }
    }
    Connections{
        target:window
        function onActiveChanged(active){
            if(active){
                textInput.y = (item.height-window.keyboardHeight) - (textInput.height)

            }else{
                textInput.y = parent.height/2-textInput.height/2
            }
        }
    }
    BusyIndicator{
        anchors.centerIn:parent
        visible:wifiListLoader.status == Loader.Loading
    }
    Component.onCompleted: {
        if(load)
            wifiListLoader.active = true
    }
    Connections{
        target:pageView
        function onBusyChanged(){
            if(!pageView.busy && !wifiListLoader.active)
                wifiListLoader.active=true;
        }
    }
    TextInputDialog{
        id:textInput
        width:parent.width/3
        height:200
        focus:true
        modal:true
        echoMode: TextField.Password
        enableOkButtom: textInput.text.length >= 8
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        inputTitle:qsTr("Enter password")
        onAccepted: {
            wifi.password = textInput.text

            wifi.sendPassword()
        }
        onRejected: {
            wifi.password =""
            wifi.sendPassword()
        }



    }

    Column{
        anchors.fill: parent
        Switch{
            text:qsTr("Wi-Fi")
            checked: wifi.powered;
            width:parent.width
            height:window.height*0.12
            onClicked: {
                wifi.powered =checked
            }


        }



        //Item{width:1;height:window.height*0.12}
        MenuSeparator{
            id:separator
            width:parent.width
        }

        Loader{
            id:wifiListLoader
            visible:wifi.powered
            width:parent.width
            height:parent.height-separator.y
            active: false
            asynchronous: true
            source:"WifiList.qml"

        }
    }
}
