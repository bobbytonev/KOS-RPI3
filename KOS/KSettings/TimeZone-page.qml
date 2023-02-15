import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.15
import HwClock 1.0
Item{
    id:timeZones
    BusyIndicator{
        anchors.centerIn: parent
        running:loader.status ==Loader.Loading

    }

    Connections{
        target:pageView
        function onBusyChanged(){
            if(!loader.active && !pageView.busy)
                loader.active =true
        }
    }

    Loader{
        id:loader
        anchors.fill: parent
        signal timezone(string str)
        active:false
        //asynchronous: true
        source:"TimeZoneContent.qml"
        visible:status ==Loader.Ready

    }

}
