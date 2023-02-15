import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
RowLayout {
    id:rowLayout
    spacing:20
    property var buttonLogic:[]
    property alias title: title.text
    property var hightlightValue

    signal clicked(var index);
    Label{
        Layout.fillWidth: true
        id:title
        Layout.fillHeight: true

    }


    Repeater{
        model:buttonLogic.length-1
        Button{

            display:Button.TextOnly
            text:""
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32

            highlighted: hightlightValue === buttonLogic[index]
            onClicked: {
                highlighted=true

                rowLayout.clicked(index);
            }


            Rectangle{
                color:buttonLogic[index]
                radius: parent.background != undefined  ? parent.background.radius : 0
                anchors.centerIn: parent
                border.color: color.hslLightness > 0.5 ? "black" : "white"
                width:parent.width
                height:parent.height
                scale:parent.highlighted ? 1.5 :1
                Behavior on scale{
                    NumberAnimation{
                        duration:200
                    }
                }
            }
        }




    }
    Button{
        text:"+"
        Layout.preferredWidth: 32
        Layout.preferredHeight: 32

        display:Button.TextOnly
        onClicked: {

        }

    }

    Item{
        Layout.preferredWidth: 16
    }
}
