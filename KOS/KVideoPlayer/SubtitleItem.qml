import QtQuick 2.0
import Subtitles 1.0
import Qt.labs.settings 1.1
Item {
    property string subtitleItem
    property alias subsItem: subs
    property alias settings: settings
    anchors.fill: parent
    Connections{
        target:mediaPlayer
        function onSourceChanged(){
                subtitleItem=""
        }
    }

    Text{
        id:subText
        text:subs.subtitle
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignHCenter
        textFormat: Text.AutoText
        style:Text.Outline
        styleColor:"black"
        width:parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        wrapMode: Text.WrapAnywhere
       // font.pointSize: parent.height*0.06
        font.pixelSize: settings.auto ?  parent.height*0.10 : settings.pSize
        color:"white"

    }
    Subtitles{
        id:subs
        videoPosition: mediaPlayer.position
        subFile:subtitleItem === "" ?  mediaPlayer.source : subtitleItem


    }
    Settings{
        id:settings
        property alias styleColor: subText.styleColor
        property alias color: subText.color
        property alias codec: subs.codec
        property bool auto: true
        property int pSize: 16
        property bool saveDuration:false
    }
}
