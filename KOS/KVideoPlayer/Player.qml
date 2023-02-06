import QtQuick 2.15
import QtMultimedia 5.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Subtitles 1.0
import DurationSaver 1.0
Item {
    id:videoItem
    property bool minimized: false
    property bool loadingIndicator: false
    property alias subtitleItem: subTitleItem


    width: parent.width
    height:parent.height
    scale:minimized && window.state !==0 ? 0.5 :1

    /*
    DurationSaver{
        id:durationSaver
        //source:mediaPlayer.source
        onProgressChanged: {

            if(progress < 90){
                mediaPlayer.seek((progress/100)*mediaPlayer.duration)
            }
        }

    }
    Connections{
        target:mediaPlayer
        function onDurationChanged(){
            durationSaver.source = mediaPlayer.source;
        }
    }

    Timer{
        running: mediaPlayer.isPlaying
        //interval: 600000
        interval:10000
        onTriggered: durationSaver.saveProgress((mediaPlayer.position/mediaPlayer.duration)*100)

    }
*/


    Rectangle{
        color:"black"
        anchors.fill: parent
        visible:window.state !== 0
        /// visible:true
    }

    Frame{
        anchors.fill: parent
        visible: minimized
        enabled: false
    }

    BusyIndicator{
        id:busyIndicator
        anchors.centerIn: parent
        visible:loadingIndicator
    }

    onMinimizedChanged: {

        if(!minimized){

            videoItem.x =0;
            videoItem.y =0;
        }
    }
    Behavior on scale{
        NumberAnimation{
            duration:200
            easing.type:Easing.InOutQuad
        }
    }

    TapHandler{
        target: output
        onDoubleTapped: {
            if(window.state !==2){
                manager.requestFullScreen()
            }
        }
        onTapped: {
            playerControls.opacity = !playerControls.opacity
            hide.start();
        }


    }
    Connections{
        target:manager
        function onBackClicked(){
            if(fileChooser.visible){
                fileChooser.visible = false
            }else if(!minimized) minimized = true

        }
    }



    DragHandler{
        target:videoItem
        enabled:  minimized && window.state !==0
        xAxis.enabled: true
        yAxis.enabled: true
        xAxis.minimum: -parent.width/4
        xAxis.maximum: parent.width/4
        yAxis.minimum: -parent.height/4
        yAxis.maximum:parent.height/4

    }




    Timer{
        id:hide
        interval:3000
        running: true
        onTriggered:{
            playerControls.opacity = 0

        }
    }






    VideoOutput{
        id:output
        anchors.fill: parent
        source:mediaPlayer

    }


    SubtitleItem{
        id:subTitleItem
    }

    Loader{
        active:!mediaPlayer.isStopped//window.state !==1||!mediaPlayer.isStopped
        asynchronous: true
        source:"PlayerControls.qml"
        anchors.fill: parent
        visible:true
        id:playerControls
        Behavior on opacity{
            NumberAnimation{
                duration:200
                easing.type: Easing.InOutQuad
            }
        }

    }
    FileChooserDialog{
        id:fileChooser

        // modal:true
        width:window.width
        y:window.headerHeight
        height:window.height -y
        //folder:"file:///home/bobby"
        //nameFilters: ["*.srt"]
        onAccepted: {
            url =url.replace("file://","")
            subTitleItem.subtitleItem = url
        }

    }






}
