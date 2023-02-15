import QtQuick 2.0
import QtQuick.Controls 2.15
Column{
    anchors.fill: parent

    Row{
        width:parent.width
        Button{
            icon.source: !style.icon_pack_reset ? "image://icons/folder-new":""
            display:Button.IconOnly
            width:window.height*0.08
            height:width
        }
        Button{

            icon.source: !style.icon_pack_reset ? "image://icons/filesystem-search":""
            display:Button.IconOnly
            width:window.height*0.08
            height:width


        }

    }

    MenuSeparator{
        id:separator
        width:parent.width
    }
}
