import QtQuick 2.15
import BluetoothManager 1.0
import QtQuick.Controls 2.15
Item {
    property bool load: false
    id:item
    Bluetooth{
        id:bt
    }
    onVisibleChanged: {
        if(!visible)textInput.visible=false
    }

    BusyIndicator{
        anchors.centerIn:parent
        visible:btListLoader.status == Loader.Loading
    }
    Component.onCompleted: {
        if(load)
            btListLoader.active = true
    }
    Connections{
        target:pageView
        function onBusyChanged(){
            if(!btListLoader.active && !pageView.busy && bt.powered )
                btListLoader.active =true
        }
    }
    TextInputDialog{
        id:textInput
        width:parent.width/3
        height:200
        focus:true
        modal:true
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        inputTitle:qsTr("Device name")
        onAccepted: {
            //bt.setAlias(textInput.text)
            bt.setProperty("setAlias",textInput.text,false)
        }



    }
    Connections{
        target:window
        function onActiveChanged(active){
            if(active){//fix
                textInput.y = (item.height-window.keyboardHeight) - (textInput.height)

            }else{
                textInput.y = parent.height/2-textInput.height/2
            }
        }
    }

    Column{
        anchors.fill: parent
        Switch{
            id:btSwitch
            text:qsTr("Bluetooth")
            checked: bt.powered
            enabled:bt.enabled
            //checkable: false
            width:parent.width
            height:window.height*0.12
            onCheckedChanged: {
                //bt.powered = checked
                bt.setProperty("setPower",checked,true);

            }


        }
        Button{
            text:qsTr("Device name: ") + bt.name
            width:parent.width
            enabled: bt.powered
            height:window.height*0.12
            onClicked: {

                textInput.open();

            }

        }
        MenuSeparator{
            id:separator
            width:parent.width
        }
        Item{width:1;height:window.height*0.06}
        Loader{
            id:btListLoader
            //visible:btSwitch.enabled && btSwitch.checked

            width:parent.width
            height:parent.height-separator.y
            active: false
            asynchronous: true
            source:"BluetoothList.qml"

        }


    }

}
