import QtQuick 2.0
import QtQuick.Controls 2.15
Dialog {
    id:control
    width: parent.width
    height:parent.height
    property bool copyFlag: true
    signal copy(string filePath);
    signal move(string filePath);

    onOpened: {
        if(copyMoveView.children.length===0)
            copyMoveView.push("main-page.qml",{itemVisible:false})
    }

    Connections{
        target:window.manager
        function onBackClicked(){

            if(copyMoveView.children.length  < 2){
                control.close()
            }
        }

    }


    StackView{
        id:copyMoveView
        property string path
        anchors.fill: parent


    }
    footer: Row{
        width:parent.width
        visible:copyMoveView.children.length>1
        Button{
            text:qsTr("Okay")
            width:parent.width/2
            height:window.height*0.08
            display:Button.TextOnly
            onClicked: {
                control.close()
                if(copyFlag)
                    control.copy(copyMoveView.path)
                else
                    control.move(copyMoveView.path)

            }
        }
        Button{
            text:qsTr("Cancel");
            width:parent.width/2
            height:window.height*0.08

            display:Button.TextOnly
            onClicked: {
                control.close()
                control.rejected()
            }

        }
    }
}
