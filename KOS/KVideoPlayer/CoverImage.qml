import QtQuick 2.15
Item{
    Image{
        id:songCover
        width:window.height/2
        height:width
         anchors.centerIn: parent
        source: !style.icon_pack_reset ? "image://icons/video-cover": ""

    }
    MouseArea{
        anchors.fill: parent
        id:mouse
        onClicked: {
            manager.requestMaximized()
        }
    }
}

