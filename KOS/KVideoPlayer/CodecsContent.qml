import QtQuick 2.0
import QtQuick.Controls 2.15
ListView {
    id:view
    anchors.fill: parent
    property var availableCodecs:["Windows-1251","UTF-8","UTF-16"
        ,"UTF-16BE","UTF-16LE","Windows-1250","Windows-1252",
        "KOI8-R","ISO 8859-6","Windows-1256","ISO 8859-7","Windows-1253"
        ,"ISO 8859-8","Windows-1255","ISO 8859-9","Windows-1254",
        ,"Windows-1257","ISO 2022-JP","EUC-JP","EUC-KR","BIG-5","Windows-1258",]
    property var availableCodecsNames:[qsTr("Cyrillic"),qsTr("Universal")
        ,qsTr("Universal"),qsTr("Universal"),qsTr("Universal"),qsTr("Universal,Chinese"),
        qsTr("Eastern,Europe"),qsTr("Western,Europe"),qsTr("Russian"),qsTr("Arabic"),qsTr("Arabic"),qsTr("Greek"),
        qsTr("Greek"),qsTr("Hebrew"),qsTr("Hebrew"),qsTr("Turkish"),qsTr("Turkish"),qsTr("Baltic"),
        qsTr("Japanese"),qsTr("Japanese"),qsTr("Korean"),qsTr("Tradition Chinese"),qsTr("Vietnamese")]

    model:availableCodecs.length
    delegate:Button{
        text:availableCodecsNames[index] +"("+availableCodecs[index]+")"
        highlighted: availableCodecs[index] === player.subtitleItem.subsItem.codec
        width:view.width
        height:window.height*0.12
        onClicked: {
            if(!highlighted){
                player.subtitleItem.subsItem.codec = availableCodecs[index]
                popup.close();
            }
        }
    }



}
