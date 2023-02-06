import QtQuick 2.0
import QtQuick.Controls 2.15

Popup {
    //color:bbb5b5b
    visible:false
    closePolicy: Popup.NoAutoClose




    BusyIndicator{
        visible:myPlayer.status == Loader.Loading
        anchors.centerIn: parent
    }
    onOpened: {
        if(!myPlayer.active){
            myPlayer.active = true
        }
    }

    Loader{
        id:myPlayer
        anchors.fill: parent
        source:"PlayerPopupContent.qml"
        active:false
        asynchronous: true

    }


}
