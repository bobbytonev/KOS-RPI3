import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
RowLayout{
    width:parent.width

    Button{
        id:volumeButtonLow
        Layout.preferredHeight: window.height*0.08
        Layout.preferredWidth:Layout.preferredHeight
        width:Layout.preferredHeight
        height:width
        display:Button.IconOnly
        icon.source:!style.icon_pack_reset ? "image://icons/brightness-low": ""


    }

    Slider{
        Layout.preferredHeight: volumeButtonLow.height
        Layout.fillWidth: true

    }
    Button{
        id:volumeButtonHigh
        Layout.preferredHeight: window.height*0.09//volumeButtonLow.height
        Layout.preferredWidth: height
        width:Layout.preferredWidth
        height:width
        display:Button.IconOnly
        icon.source:!style.icon_pack_reset ? "image://icons/brightness-high": ""


    }

}
