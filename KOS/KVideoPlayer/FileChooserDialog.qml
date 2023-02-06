import QtQuick 2.15
import QtQuick.Controls 2.12
import Qt.labs.folderlistmodel 2.15

Dialog {
    id:dialog

    property alias folder: folderModel.folder
    property alias nameFilters: folderModel.nameFilters
    property string url:""

    FolderListModel {
        id: folderModel
        showDirsFirst: true
        folder:{
            var mSource =mediaPlayer.source.toString();
            return mSource.substring(0,mSource.lastIndexOf("/"));



        }
        nameFilters: ["*.srt"]
        rootFolder: "file://"+_homeDir




    }

    onOpened:{
        var mSource =mediaPlayer.source.toString();
        folderModel.folder= mSource.substring(0,mSource.lastIndexOf("/"));
    }


    header:Button{
        text:title
        id:control
        height:window.height * 0.10

        icon.source:!style.icon_pack_reset ? "image://icons/system-back" : ""

        MenuSeparator{
            width: parent.width
            y:control.height

        }
        onClicked:{

            if(folderModel.folder.toString() != folderModel.rootFolder.toString()){

                var folder2 = folderModel.folder
                folderModel.folder = folder2.toString().substring(0,folder2.toString().lastIndexOf("/"));


            }

        }
        onPressAndHold:{ dialog.rejected();dialog.close()}

    }

    Item{

        anchors.fill: parent

        ListView{

            id:view
            anchors.fill: parent
            clip:true
            spacing:5
            model:folderModel
            delegate:Button{

                text:fileName
                width: view.width
                icon.source: !style.icon_pack_reset ? folderModel.isFolder(index) ? "image://icons/folder":"image://icons/file" : ""



                icon.cache: false
                height: window.height*0.12

                onClicked: {

                    if(folderModel.isFolder(index)){
                        folderModel.folder=fileUrl

                    }else{
                        url=fileUrl
                        dialog.accepted()
                        dialog.close()

                    }
                }
            }

        }

    }

    footer:Item{}


}
