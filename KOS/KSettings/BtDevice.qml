import QtQuick 2.12
import BluetoothDevice 1.0
import QtQuick.Controls 2.15
SwipeDelegate {
    id:control
    BluetoothDevice{
        id:btDevice

        devicePath: objectPath


    }



    swipe.onCompleteChanged: {

        swipe.rightItem.scale = swipe.complete

    }
    onClicked: {
        if( !(btDevice.connected&&btDevice.paired))
            btDevice.makeConnection();
    }



    highlighted: btDevice.connected&&btDevice.paired
    height:window.height*0.12
    text:btDevice.name
    icon.source: !style.icon_pack_reset ? "image://icons/"+ btDevice.icon:""
    swipe.right: Item{
        id:row
        width:parent.height*2
        height:width/2
        scale:0
        anchors.right: parent.right
        Behavior on scale{
            NumberAnimation{
                duration:150
            }
        }


        //Button{
          //  icon.source: !style.icon_pack_reset ? "image://icons/info":""
           // width:parent.height
           // height:width
            //visible:false
            ///anchors.right: parent.right
        //}
        Button{
            property bool connected: btDevice.connected
            icon.source: !style.icon_pack_reset ?
                             "image://icons/"+(connected ? "disconnect":"delete"):""
            width:parent.height
            height:width
            anchors.centerIn: parent
            display:Button.IconOnly
            onClicked: {
                if(connected){
                    btDevice.disconnect();
                    swipe.close()
                }else{
                    btDevice.removeDevice();
                }
            }

            //anchors.right: parent.right
        }
    }


}
