import QtQuick 2.15
import QtQuick.Controls 2.15
import UsbModel 1.0
import QtMultimedia 5.15
import WindowManager 1.0
import DurationSaver 1.0
ApplicationWindow {
    id:window
    width: 1024
    height: 600
    visible: true
    property int state:1
    property alias mediaPlayer: mediaPlayer
    property alias playList: playList
    property real headerHeight:-1
    property alias manager: manager



    Component.onCompleted: {
        if(window.header != undefined){
            headerHeight=window.header.height

        }
        if(videoFile !==""){

            mediaPlayer.source = videoFile;
        }
    }

    WindowManager{
        id:manager



        onStateChanged:(state)=>{

                           if(window.state !== state){
                               window.state=state;
                               player.minimized = false

                               if(headerHeight !==-1){
                                   if(state === 2 ){
                                       window.header.height=0
                                   }else{
                                       window.header.height = headerHeight
                                   }
                               }
                           }
                       }

    }


    CustomPlaylist{
        id:playList
    }




    MediaPlayer{
        id:mediaPlayer
        property string videoTitle
        property bool isPlaying: false
        property bool isStopped: true

        autoPlay:true

        onPaused: {
            isStopped=false
            isPlaying=false;



        }
        onPlaying: {

            isStopped=false
            isPlaying=true;

        }
        onIsStoppedChanged: {

            if(isStopped){
                isPlaying = false;

            }


        }
        onStatusChanged: {
            if(status == MediaPlayer.EndOfMedia){

                playList.nextVideo();
            }
        }



        onSourceChanged: {
            var fileName = mediaPlayer.source.toString().split("/");
            mediaPlayer.videoTitle = fileName[fileName.length-1];
        }
        onError: {
            if(error == Audio.ResourceError
                    || error == Audio.FormatError || error == Audio.AccessDenied)
                playList.stop();
        }



    }

    Storage{
        anchors.fill: parent
        visible:window.state === 1//!player.visible || (player.minimized&&window.state !=0)


    }

    background:Item{
        z:99
        Player{
            id:player
            visible:!mediaPlayer.isStopped
            loadingIndicator:mediaPlayer.status == MediaPlayer.Loading



        }
    }

    Loader{
        id:coverLoader
        active: window.state === 0 && !player.visible
        anchors.fill: parent
        source:"CoverImage.qml"
    }




}


