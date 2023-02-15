import QtQuick 2.0
import QtQuick.Controls 2.15
import ApplicationInfo 1.0
Item {
    id:item
    property var translations:[qsTr("Path:"),qsTr("Category:"),qsTr("Version:")]
    ApplicationInfo{id:application;configPath: information.confLocation}
    ListView{
        id:view
        anchors.fill:parent
        model:1
        delegate:Column{
            spacing:20
            width: parent.width
            Button{
                width: parent.width
                display:Button.TextUnderIcon
                text:application.name
                icon.source: !style.icon_pack_reset ? "image://icons/"+application.icon:""

                height: window.height*0.20
                enabled:false
            }

            Row{
                id: row;
                property alias deleteButton:deleteButton

                width: parent.width
                Button{
                    id:deleteButton
                    display:Button.TextOnly
                    visible:false
                    height:window.height*0.12
                    text:qsTr("UNISTALL")
                    width: parent.width/2
                    onClicked:{
                    }
                }
                Button{
                    display:Button.TextOnly
                    text:qsTr("FORCE CLOSE")
                    visible:false
                    width: parent.width/2
                    height:window.height*0.12
                    onClicked:{

                    }
                }
            }

            MenuSeparator{
                width:parent.width
            }

            Repeater{
                model:application.info.length
                Label{
                    text:translations[index]+application.info[index]
                    height:74
                }
            }








        }

    }

}
