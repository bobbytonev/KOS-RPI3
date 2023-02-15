import QtQuick 2.0
import QtQuick.Controls 2.15
import UsbModel 1.0
Column{
    id:column
    spacing:20
    property bool itemVisible: true
    Item{
        id:item
        visible:itemVisible
        width:parent.width
        height:row.height
        Row{

            property var buttonNames:[qsTr("Audio"),qsTr("Video"),qsTr("Images")]
            property var imageName: ["sound","videos","pictures"]
            property var types:["/Audio","/Video","/Image"]

            id:row
            spacing:20
            anchors.centerIn: parent
            height:window.height*0.20
            Repeater{
                model:row.buttonNames.length
                Button{
                    width:parent.height
                    height:width
                    text:row.buttonNames[index]
                    display:Button.TextUnderIcon
                    icon.source: !style.icon_pack_reset ? "image://icons/folder-"+row.imageName[index]:""
                    onClicked: {

                        window.stackView.push("InternalFiles.qml",{fileType:row.types[index],iconName:icon.source});

                    }


                }
            }

        }
    }
    ListView{
        id:view
        width:parent.width
        height:column.height-row.height
        model:UsbModel{}
        spacing:20


        delegate:Button{
            icon.source: !style.icon_pack_reset ? "image://icons/usb":""
            text:deviceName
            width:view.width
            height:window.height*0.12

            onClicked: {
                if(itemVisible)
                    window.stackView.push("storage.qml",{startingFolder:moutingPoint})
                else
                    column.parent.push("storage.qml",{startingFolder:moutingPoint,foldersOnly:true});
            }
        }


        header:Column{
            width:view.width

            Button{
                icon.source: !style.icon_pack_reset ? "image://icons/drive-harddisk":""
                text:qsTr("Main storage")
                width:parent.width
                height:window.height*0.12
                onClicked: {
                    if(itemVisible)
                        window.stackView.push("storage.qml",{startingFolder:_homeDir+"/str"})
                    else
                        column.parent.push("storage.qml",{startingFolder:_homeDir+"/str",foldersOnly:true});
                }
            }
            MenuSeparator{
                width:parent.width
                visible:view.count > 0
            }
        }
    }
}
