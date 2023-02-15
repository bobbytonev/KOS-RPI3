import QtQuick 2.15
import Qt.labs.folderlistmodel 2.15
import QtQuick.Controls 2.15
Item{
    anchors.fill:parent

    Label{
        anchors.fill:parent
        visible:usbStorage.count === 0
        text:qsTr("Empty folder")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    Connections{
        target:manager
        function onBackClicked(){
            if(visible&&displayFileModel.folder.toString() != displayFileModel.rootFolder.toString()){

                var folder2 = displayFileModel.folder
                displayFileModel.folder = folder2.toString().substring(0,folder2.toString().lastIndexOf("/"));


            }

        }
    }

    ListView{
        id:usbStorage


        property bool folderChanged: displayFileModel.folder.toString()
                                     != fileModel.folder.toString()
        property bool isModelActive:false
        Connections{
            target:playList
            function onPlayListModelChanged(){

                usbStorage.isModelActive = playList.playListModel === fileModel ||
                        playList.playListModel === displayFileModel
            }
        }
        anchors.fill: parent
        FolderListModel{
            property int lastCount : fileModel.count
            id:fileModel
            showDirsFirst:true


            nameFilters: [ "*.mp4", "*.avi","*.mkv" ]
            onStatusChanged: {
                if(status == FolderListModel.Ready&&usbStorage.isModelAcitve){
                    playList.playListModel = fileModel
                }
            }
            onCountChanged: {

                if(fileModel.lastCount > fileModel.count){
                    if(usbStorage.isModelActive){
                        playList.stop();
                    }
                }
                lastCount = fileModel.count
            }

        }
        FolderListModel{
            nameFilters: [ "*.mp4", "*.avi","*.mkv" ]
            showDirsFirst: true
            id:displayFileModel
            folder:"file://"+usbLoader.usbMoutingPoint//"file:///home/bobby"
            rootFolder: "file://"+usbLoader.usbMoutingPoint
            //folder:"file://"+_homeDir
            //rootFolder: "file://"+_homeDir //fix me

        }


        Component.onDestruction: {

            if(isModelActive){
                playList.stop()
            }
        }
        model:displayFileModel
        delegate:Button{
            property bool folder:displayFileModel.isFolder(index)
            width:usbStorage.width
            height:window.height*0.12
            text:fileName
            highlighted: usbStorage.isModelActive&&!usbStorage.folderChanged&&playList.currentIndex === index
            icon.source: !style.icon_pack_reset ? "image://icons/"+(folder ? "folder":"video-cover"): ""


            onClicked: {


                if(folder){ displayFileModel.folder = fileUrl;return}

                if(usbStorage.folderChanged || !usbStorage.isModelActive){
                    fileModel.folder = displayFileModel.folder
                    playList.playListModel = displayFileModel



                }
                if(playList.currentIndex === index){
                      playList.currentIndex = -1;

                }
                  playList.currentIndex = index


            }

        }


    }

}

