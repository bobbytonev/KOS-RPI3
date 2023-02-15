import QtQuick 2.0
import AllApplications 1.0
import QtQuick.Controls 2.12
Item {
    id:item
    BusyIndicator{
        id:indicator
        z:2
        anchors.centerIn: parent
        running:apps.running
    }
    Component.onCompleted:{
        //apps.active = true
    }

    Connections{
        target:pageView
        function onBusyChanged(){
            if(!apps.active && !pageView.busy) apps.active = true
        }

    }

    AllApplications{id:apps;language:lang.language}
    ListView{
        id:view
        anchors.fill: parent
        model:apps
        maximumFlickVelocity:5000
        delegate:Button{
            height:window.height*0.12
            width:view.width
            text:name
            icon.source: !style.icon_pack_reset ? "image://icons/"+ appIcon:""
            onClicked:{
                window.pageView.push("AppInfo-page.qml",{confLocation:confPath});
            }
        }

    }
}
