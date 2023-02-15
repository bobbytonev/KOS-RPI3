import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import InternalVideoModel 1.0
Item{
    Label{
        anchors.fill:parent
        visible:view.count === 0
        text:qsTr("No video found")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    ListView{

        property bool isModelActive:false
        id:view
        anchors.fill: parent
        model:InternalVideoModel{}
        Connections{
            target:playList
            function onPlayListModelChanged(){
                view.isModelActive = playList.playListModel === view.model
            }
        }
        Connections{
            target:view.model
            function onRowsRemoved(modelIndex,first,last){
                if(view.isModelActive && first === playList.currentIndex){
                    playList.stop();
                }
            }
        }


        delegate:Button {
            text:fileName
            width:view.width
            height:window.height* 0.12
            highlighted:view.isModelActive&&playList.currentIndex === index
            icon.source: !style.icon_pack_reset ? "image://icons/video-cover": ""
            onClicked: {

                if(!view.sModelActive){

                    playList.playListModel = view.model;
                }


                playList.currentIndex = index
            }



        }
    }
}
