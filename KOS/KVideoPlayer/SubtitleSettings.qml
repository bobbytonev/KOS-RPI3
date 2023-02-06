import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
//ListView{
//  model:1
// property var names:[qsTr("Outline color"),qsTr("Text color")]
//property int colorIndex
//delegate:Column {
//width:parent.width
Column{
    property var names:[qsTr("Outline color"),qsTr("Text color")]
    property int colorIndex
    spacing:20

    Repeater{
        model:names.length
        Button{
            text:names[index]
            width:parent.width
            height:parent.height*0.12
            onClicked: {
                colorDialog.initColorValue = index === 0 ? player.subtitleItem.settings.styleColor:
                                                           player.subtitleItem.settings.color
                colorDialog.open()

                colorIndex = index
            }
        }
    }
    ColorChooserDialog{
        id:colorDialog

        onAccepted: {
            if(colorIndex === 0){
                player.subtitleItem.settings.styleColor =colorDialog.colorValue
            }else{
                player.subtitleItem.settings.color =colorDialog.colorValue
            }
        }
    }

    Button{
        id:codecButton
        text:qsTr("Codec")
        width:parent.width
        height:parent.height*0.12
        onClicked: {
            codecs.open()
        }

    }
    MenuSeparator{
        width:parent.width
    }

    Switch{
        id:autoSwitch
        checked:player.subtitleItem.settings.auto
        text:qsTr("Auto size")
        width:parent.width
        height:codecButton.height
        onClicked: {
            player.subtitleItem.settings.auto=!player.subtitleItem.settings.auto
        }
    }
    RowLayout{
        width:parent.width
        height:codecButton.height
        enabled:!autoSwitch.checked
        Label{
            text:qsTr("Size")
        }
        Slider{
            Layout.fillWidth: true
            from:16
            value:player.subtitleItem.settings.pSize
            stepSize: 1
            to:96
            onMoved: player.subtitleItem.settings.pSize=value
        }

    }
    /*
        MenuSeparator{
            width:parent.width
        }
        Switch{
            width:parent.width
            height:window.height*0.12
            text:qsTr("Save video duration")
            checked: player.subtitleItem.settings.saveDuration;
            onClicked: {
                player.subtitleItem.settings.saveDuration=!player.subtitleItem.settings.saveDuration

            }
        }
*/
    Codecs{
        id:codecs;
        width:parent.width
        //y:parent.height-height+20
        //height:parent.height/1.5

    }


    //}


}
