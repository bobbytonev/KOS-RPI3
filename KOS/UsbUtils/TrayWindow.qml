import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
ApplicationWindow {

    visible: true
   id:root
   width:24
   height:24
   color:"Transparent"
    Image{
       source:!style.icon_pack_reset ? "image://icons/usb-tray-icon" : ""
       anchors.fill: parent
       smooth: true
       //mipmap: true
       //antialiasing: true
    MouseArea{
        anchors.fill: parent
        onClicked: {
           // var comp = Qt.createComponent("KDialog.qml");
           // var window =comp.createObject(root);
           // window.show();
            child.visible=true
        }

    }

   }

}
