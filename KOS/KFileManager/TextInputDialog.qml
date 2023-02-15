import QtQuick 2.0
import QtQuick.Controls 2.15

Dialog {

    id:textDialog
    property alias inputTitle: label.text
    property alias text: textInput.text
    property alias echoMode: textInput.echoMode
    property bool enableOkButtom:true



    contentItem: Column{
        spacing:5
        Label{
            width:parent.width
            id:label
            horizontalAlignment: Text.AlignHCenter

        }
        TextField{
            focus:true
            id:textInput
            width:parent.width

        }
    }

    onOpened:{
        textDialog.focus = true
        textInput.focus = true

    }

    header:Item{}
    footer: Row{
        width:parent.width
        Button{
            text:qsTr("Okay")
            width:parent.width/2
            height:window.height*0.10
            enabled: enableOkButtom
            display:Button.TextOnly
            onClicked: {
                textDialog.accepted()
                textDialog.close()
            }
        }
        Button{
            text:qsTr("Close")
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
