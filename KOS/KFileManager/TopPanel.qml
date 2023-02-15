import QtQuick 2.15
import QtQuick.Controls 2.15
Row{
    //visible:!foldersOnly
    //width:parent.width
    onVisibleChanged: {
        if(!visible)
            menu.visible=false

    }

    Button{
        id:fileMenu
        icon.source: !style.icon_pack_reset ? "image://icons/application-menu":""
        visible:highlightedSize > 0 && !searchField.visible
        display:Button.IconOnly
        width:window.height*0.08
        height:width

        onClicked: {
            menu.open()
        }

        Menu{
            id:menu

            MenuItem{
                id:deleteItem
                text:qsTr("Detele");
                height:window.height*0.08
                onClicked: {
                    col.deleteFiles()
                }
            }
            MenuItem{
                height:deleteItem.height
                text:qsTr("Copy")

                onClicked: {
                    copyMove.copyFlag = true
                    copyMove.open()
                }
            }
            MenuItem{
                height:deleteItem.height

                text:qsTr("Move")
                onClicked: {
                    copyMove.copyFlag = false
                    copyMove.open()
                }
            }
            MenuItem{
                height:deleteItem.height

                text:qsTr("Rename")
                enabled:highlightedSize < 2
                onClicked: {
                    textInput.newFolder = false
                    textInput.focus = true
                    textInput.open()
                }
            }
            MenuSeparator{
                width:parent.width
            }
            MenuItem{
                height:deleteItem.height

                text:qsTr("Select all")
                onClicked: {
                    col.selectAll()
                }

            }
            MenuItem{
                height:deleteItem.height
                text:qsTr("Diselect all")
                onClicked: {
                    col.deselectAll()
                }

            }

        }
    }
    BusyIndicator{
        running:fileManager.running
        visible:running
        width:window.height*0.08
        height:width

    }
    Label{
        visible:fileManager.running
        text:fileManager.progress+"/"+fileManager.max
    }

    Button{
        icon.source: !style.icon_pack_reset ? "image://icons/folder-new":""
        display:Button.IconOnly
        visible: !searchField.visible
        width:window.height*0.08
        height:width
        onClicked: {
            textInput.newFolder = true
            textInput.focus = true
            textInput.open()
        }
    }
    Button{

        icon.source: !style.icon_pack_reset ? "image://icons/filesystem-search":""
        display:Button.IconOnly
        width:window.height*0.08
        height:width
        onClicked: {

            searchField.visible = !searchField.visible
        }


    }
    TextField{
        id:searchField
        visible:false
        height: window.height*0.08
        onVisibleChanged: {
            if(visible)
                searchField.focus = true
            else
                text=""
        }
        onTextChanged: {
            col.search(text);
        }



    }

}
