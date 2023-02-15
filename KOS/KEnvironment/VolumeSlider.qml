import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import VolumeControl 1.0
RowLayout{
    width:parent.width
    VolumeControl{
        property real actualVolume: (100/max)*volume
        id:volumeControl
    }
    Button{
        id:volumeButtonLow
        //visible:false
        Layout.preferredHeight: window.height*0.08
        Layout.preferredWidth: height
        width:Layout.preferredHeight
        height:width
        display:Button.IconOnly
        icon.source:!style.icon_pack_reset ?"image://icons/audio-volume-low-panel" :""
    }

    Slider{
        id:slider
        Layout.fillWidth :true
        Layout.preferredHeight:volumeButtonLow.height
        value: volumeControl.volume
        stepSize:1
       // from:volumeControl.min
        //to:volumeControl.max
        from:0
        to:100
        onMoved: {
            volumeControl.volume=value;
        }




    }
    Button{
        id:volumeButtonHigh

        Layout.preferredHeight: window.height*0.09//volumeButtonLow.height
        Layout.preferredWidth: height
        width:Layout.preferredHeight
        height:width
        display:Button.IconOnly
        icon.source:!style.icon_pack_reset ?"image://icons/audio-volume-high-panel" :""



    }

}
