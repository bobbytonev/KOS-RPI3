import QtQuick 2.0

Item {

    Image{
        width:window.height/4
        height:width
        anchors.centerIn: parent
        visible:window.state === 0
        cache:false
        source: !style.icon_pack_reset ? "image://icons/com.kos.filemanager": ""

    }


    MouseArea{
        visible:window.state === 0
        anchors.fill: parent
        onClicked: {
            manager.requestMaximized();

        }
    }
}
