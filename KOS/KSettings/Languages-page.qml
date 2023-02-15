import QtQuick 2.0
import QtQuick.Controls 2.12
Item {

    Loader{
        id:loader
        anchors.fill: parent
        source:"LanguageContent.qml"
        active:true
        visible:status==Loader.Ready
        asynchronous: true
    }
    BusyIndicator{
        anchors.centerIn: parent
        running:loader.status==Loader.Loading


    }
    Connections{
        target:pageView
        function onBusyChanged(){
            if(!loader.active && !pageView.busy)
                loader.active =true
        }
    }


}
