import QtQuick 2.0
import QtQuick.Controls 2.15
Popup{
    visible:false
    id:popup
    modal:true
    BusyIndicator{
        anchors.centerIn: parent
        visible:loader.status == Loader.Loading
    }
    Connections{
        target:window.manager
        function onBackClicked(){
            popup.close()
        }
        function onStateChanged(state){
              if(state === 0 && popup.visible) popup.close();
        }
    }
    onOpened: {
        if(!loader.active)
            loader.active = true
    }

    //Pane{
      //  anchors.fill: parent
        Loader{
            id:loader
            asynchronous: true

            source:"CodecsContent.qml"
            width:parent.width
            height:parent.height - window.height * 0.12
            y:parent.height - height
        }
    //}
}
