import QtQuick 2.0
import QtQuick.Controls 2.2
Item {

    property  var  names: [qsTr("Ram"),qsTr("Free Ram"),qsTr("Cpu name")
        ,qsTr("Cpu clock"),qsTr("Cpu cache"),qsTr("Kernel")]

    Component.onCompleted: {
        info.reload();
    }


    ListView{
        id:view
        anchors.fill: parent
        clip: true
        model:info.info.length
        delegate:Label{
            text:names[index]+":\n"+info.info[index];
            height:window.height*0.12
        }
    }

}
