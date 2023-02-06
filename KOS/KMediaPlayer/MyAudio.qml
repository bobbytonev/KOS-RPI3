import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import InternalAudioModel 1.0
ListView{
    //anchors.fill: parent
    property bool isModelActive:false
    id:view
    model:InternalAudioModel{}
    Connections{
        target:playList
        function onPlayListModelChanged(){
            isModelActive = playList.playListModel === view.model
        }
    }
    Connections{
        target:model
        function onRowsRemoved(modelIndex,first,last){
            if(view.isModelActive&&first === playList.currentIndex){
                playList.stop();
            }
        }
    }


    delegate:Button {
        property var testINdex: index
        text:fileName
        width:view.width
        height:window.height* 0.12
        highlighted:isModelActive&&playList.currentIndex === index
        icon.source: !style.icon_pack_reset ? "image://icons/audio-cover": ""
        onClicked: {


            if(!isModelActive){

                playList.playListModel = view.model;
            }


            playList.currentIndex = index
        }



    }
}
