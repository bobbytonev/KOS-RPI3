import QtQuick 2.15
import QtQuick.Controls 2.15
import UsbModel 1.0
import QtMultimedia 5.15
import WindowManager 1.0
ApplicationWindow {
    id:window
    width: 1024
    height: 600
    visible: true
    property alias audioPlayer: audioPlayer
    property alias playList: playList
    property alias manager: manager
    property int state:1;



    CustomPlaylist{
        id:playList
    }
    Component.onCompleted: {
        if(musicFile !==""){

            audioPlayer.source = musicFile;
        }
    }

    Audio{

        property string songTitle
        property bool isPlaying: false
        property bool isStopped: true
        autoPlay: true
        autoLoad: true

        id:audioPlayer

        onPaused: {
            isStopped=false
            isPlaying=false;
        }
        onPlaying: {
            isStopped=false
            isPlaying=true;

        }
        onIsStoppedChanged: {
            if(isStopped) isPlaying = false
        }


        onStopped:{

            //isStopped=true
            //isPlaying=false;
            //songTitle = ""


        }
        onStatusChanged: {
            if(status == Audio.EndOfMedia){

               if(!playList.nextSong()) isStopped = true
            }
        }





        onSourceChanged: {

            var fileName = audioPlayer.source.toString().split("/");

            audioPlayer.songTitle = fileName[fileName.length-1];

        }

        onError: {

            if(error == Audio.ResourceError
                    || error == Audio.FormatError || error == Audio.AccessDenied)
                playList.nextWithoutAutoReturn()
        }

    }


    WindowManager{
        id:manager
        onBackClicked:(pid)=> {
                          if(playerControl.visible){
                              playerControl.close()
                          }else if(swipeView.currentIndex < 2){
                              Qt.callLater(Qt.quit)
                          }
                      }
        onStateChanged:(state)=>{

                           if(window.state !== state){


                               window.state=state;

                           }
                       }
    }


    onWidthChanged: {
        console.log("WIDTH CHANGED:",width,state);
    }


    SwipeView {
        id: swipeView
        visible:!playerControl.visible
        anchors.fill: parent
        anchors.topMargin:tabBar.visible ?  tabBar.height+20 : 0
        currentIndex:!interactive&&currentIndex !==1 ? 1: tabBar.currentIndex
        anchors.bottomMargin:bottomPlayer.height
        interactive: window.state !==0



        onCurrentIndexChanged: {
            if(!btLoader.active&&currentIndex===1){
                btLoader.active = true
            }


        }


        Item{
            BusyIndicator{
                visible:myAudio.status == Loader.Loading
                anchors.centerIn: parent
            }
            Loader{
                id:myAudio
                anchors.fill: parent
                source:"MyAudio.qml"
                active:true
                asynchronous: true


                onStatusChanged: {
                    if(status === Loader.Ready){
                        playerLoader.active = true
                    }
                }
            }
        }
        Item{
            BusyIndicator{
                visible:btLoader.status == Loader.Loading
                anchors.centerIn: parent
            }
            Loader{
                id:btLoader
                anchors.fill: parent
                asynchronous: true
                active:false
                source:"Bluetooth.qml"

            }
        }

        Repeater{
            model:usbModel
            delegate:Loader{
                id:usbLoader
                property string usbMoutingPoint:moutingPoint

                active:true
                source:"Usb.qml"
                asynchronous: true


            }
        }
    }
    UsbModel{
        id:usbModel
    }


    TabBar {
        id: tabBar
        visible:swipeView.visible&&window.state !==0

        //anchors.horizontalCenter: parent
        //x:parent.width/2 - width/2
        spacing: 20
        width: parent.width
        position: TabBar.Header
        currentIndex: swipeView.currentIndex

        background: Rectangle{
            color:"transparent"
        }


        TabButton {
            text: qsTr("Music");
        }

        TabButton {
            text: qsTr("Bluetooth")


        }
        Repeater{
            model:usbModel
            delegate:TabButton {
                text:deviceName


            }
        }



    }



    PlayerControlPopup{
        id:playerControl
        width:parent.width
        height:parent.height
        onOpened: {

        }
    }

    Frame{
        id:bottomPlayer
        height:window.height*0.15
        width:parent.width
        visible:!playerControl.visible&&!audioPlayer.isStopped
        anchors.bottom: parent.bottom
        MouseArea{
            anchors.fill: parent
            onPressed: {
                if(window.state)
                    playerControl.open()
            }
        }
        Loader{
            id:playerLoader
            active:true
            asynchronous: true
            anchors.centerIn: parent
            width:parent.width-parent.height

            source:"Player.qml"


        }
    }






}
