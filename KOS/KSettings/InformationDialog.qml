import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id:textDialog
    property alias text: label.text
    x:parent.width/2-width/2
    y:parent.height/2-height/2
    modal:true
   // width:200


    header:Item{height:0}
    contentItem: Label{
        id:label
       // anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        leftPadding: 0
        rightPadding: 0

    }



    onOpened:{
        textDialog.focus = true
        textInput.focus = true

    }


    footer: Row{
        width:parent.width
        Button{
            text:qsTr("Yes")
            width:parent.width/2
            height:window.height*0.10

            display:Button.TextOnly
            onClicked: {
                textDialog.accepted()
                textDialog.close()
            }
        }
        Button{
            text:qsTr("No")
            width:parent.width/2
            height:window.height*0.10
            display:Button.TextOnly
            onClicked: {
                textDialog.rejected()
                textDialog.close()

            }
        }
    }


}
