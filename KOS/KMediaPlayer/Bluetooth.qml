import QtQuick 2.0
import BluetoothDeviceModel 1.0

import QtQuick.Controls 2.15
Item {
    anchors.fill: parent

    Component.onCompleted: {
        if( window.state === 0){
            if(view.count > 0 ){
                playerControl.close()
            }else{
                playerControl.open()
            }
        }
    }

    Connections{
        target:window
        function onStateChanged(){

            if(window.state ===0){
                if(view.count > 0 ){
                    playerControl.close()
                }else{
                    playerControl.open()
                }
            }
        }
    }

    ListView{
        id:view
        anchors.fill: parent
        clip:true
        spacing:20
        onCountChanged:{
            if(count === 0 && window.state === 0){
                playerControl.open();
            }else{
                playerControl.close()
            }
        }

        model:BluetoothDeviceModel{id:btModel}
        snapMode:ListView.SnapOneItem
        delegate: BtPlayer{
            width:view.width

            height:window.state === 0 ? view.height : window.height*0.12
            deviceName: name
            devicePath: objectPath
            deviceIcon:!style.icon_pack_reset ? "image://icons/"+icon: ""
            onPlay:btModel.sendCommand("Play",objectPath);
            onPause:btModel.sendCommand("Pause",objectPath);
            onNext:btModel.sendCommand("Next",objectPath);
            onPrevious:btModel.sendCommand("Previous",objectPath);




        }

    }

}
