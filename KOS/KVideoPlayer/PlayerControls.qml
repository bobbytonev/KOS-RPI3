import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Column{

    id:playerControls
    anchors.fill: parent
    spacing:20
    enabled:parent.opacity === 1



    function msToTime(duration) {
        var milliseconds=parseInt((duration%1000)/100),
        seconds = Math.floor((duration / 1000) % 60),
        minutes = Math.floor((duration / (1000 * 60)) % 60),
        hours = Math.floor((duration / (1000 * 60 * 60)) % 24);

        var displayHours = hours !== 0

        hours = (hours < 10) ? "0" + hours : hours;
        minutes = (minutes < 10) ? "0" + minutes : minutes;
        seconds = (seconds < 10) ? "0" + seconds : seconds;


        return (displayHours ? hours + ":":"") + minutes + ":" + seconds;
    }




    Item{
        width:parent.width
        height:window.headerHeight
    }

    Row{
        width:parent.width


        Button{
            display:Button.IconOnly
            id:minimizedButton
            width:rotation === 180 ? playerControls.height*0.15 : playerControls.height*0.10
            height:width
            icon.source: !style.icon_pack_reset ? "image://icons/go-down": ""
            rotation: window.state === 0 || minimized  ? 180 : 0
            Behavior on rotation{
                NumberAnimation{
                    duration:200
                    easing.type: Easing.InOutQuad
                }
            }
            onClicked: {

                if(window.state !==1){
                    manager.requestMaximized()

                }else{
                    minimized = !minimized
                }



            }

        }

        Button{
            id:fullScreen
            display:Button.IconOnly
            width:minimizedButton.height
            height:width
            visible:window.state !==2
            icon.source: !style.icon_pack_reset ? "image://icons/view-fullscreen": ""
            onClicked: {
                manager.requestFullScreen()
                minimized = false

            }

        }
        Button{
            display:Button.IconOnly
            width:minimizedButton.height
            height:width
            visible:!minimized&&window.state !==0
            icon.source: !style.icon_pack_reset ? "image://icons/media-view-subtitles": ""
            onClicked: {
                fileChooser.open();

            }
        }


    }
    Item{
        width:parent.width
        height:parent.height - (y+bottomLayout.height+title.height+3*spacing)

        Row{
            id:row
            spacing:20
            anchors.centerIn: parent
            RoundButton{
                id:backward
                icon.source: !style.icon_pack_reset ? "image://icons/media-playback-back": ""
                display:Button.IconOnly
                width:videoItem.height*0.25
                height:width
                icon.width: width/2
                icon.height: height/2
                onClicked: {
                    playList.previousVideo()
                }
            }
            RoundButton{
                id:play
                width:backward.width
                height:width
                icon.source: !style.icon_pack_reset ?
                                 "image://icons/media-playback-"+(mediaPlayer.isPlaying?
                                                                      "pause":"start"): ""
                display:Button.IconOnly
                icon.width: width/2
                icon.height: height/2
                onClicked: {
                    if(mediaPlayer.isPlaying){
                        mediaPlayer.pause()


                    }else{
                        mediaPlayer.play()

                    }
                }
                onPressAndHold: playList.stop()
            }
            RoundButton{
                id:forward
                width:backward.width
                height:width
                icon.source: !style.icon_pack_reset ? "image://icons/media-playback-next": ""
                display:Button.IconOnly
                icon.width: width/2
                icon.height: height/2
                onClicked: {
                    playList.nextVideo()
                }
            }
        }
    }

    Label{
        id:title
        width:parent.width
        text:mediaPlayer.videoTitle
        horizontalAlignment:Text.AlignHCenter

    }
    RowLayout{
        id:bottomLayout

        width:parent.width




        Label{
            id:currentTime
            // text:mediaPlayer.isStopped ? "--/--":new Date(mediaPlayer.position).toLocaleTimeString(Qt.locale(),"hh:mm:ss");
            text:mediaPlayer.isStopped ? "--/--" : msToTime(mediaPlayer.position)

        }
        Slider{
            id:songPosition
            Layout.fillWidth: true

            to:1.0
            // from:0.01
            //value:mediaPlayer.position
            value:mediaPlayer.position / mediaPlayer.duration
            onMoved: {
                if(mediaPlayer.isPlaying) mediaPlayer.pause()

                mediaPlayer.seek(value*mediaPlayer.duration)

            }





        }
        Label{
            id:maxTime
            //  text:mediaPlayer.isStopped ? "--/--":new Date(mediaPlayer.duration).toLocaleTimeString(Qt.locale(""),"hh:mm:ss");
            text:mediaPlayer.isStopped ? "--/--" : msToTime(mediaPlayer.duration)

        }
    }



}
