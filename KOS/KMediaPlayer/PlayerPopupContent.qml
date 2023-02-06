import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
Column {
    spacing:20
    anchors.fill: parent

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

    Button{
        width:window.height*0.08
        height:width
        display:Button.IconOnly
        visible:window.state !==0
        icon.source: !style.icon_pack_reset ? "image://icons/go-down": ""
        onClicked: {
            close();
        }

    }
    Item{
        id:item
        width:parent.width
        height:songCover.height+50
        Image{
            id:songCover
            width:window.state !==0 ? window.height*0.30:window.height*0.20
            height:width
            anchors.centerIn: parent
            cache:false
            source: !style.icon_pack_reset ? "image://icons/audio-cover": ""





            MouseArea{
                anchors.fill: parent
                visible:window.state ===0
                onClicked:{
                    window.manager.requestMaximized()
                }
            }


        }
    }


    Label{
        width:parent.width
        text:window.audioPlayer.songTitle
        horizontalAlignment:Text.AlignHCenter
    }


    RowLayout{
        visible:window.state !==0
        width:parent.width

        onVisibleChanged: {
            if(!visible) Layout.preferredWidth = 0
        }

        Label{
            id:currentTime
            // text:audioPlayer.isStopped ? "--/--":new Date(audioPlayer.position).toLocaleTimeString(Qt.locale(),"mm:ss");
            text:audioPlayer.isStopped ? "--/--" : msToTime(audioPlayer.position);

        }
        Slider{
            id:songPosition
            Layout.fillWidth: true
            to:audioPlayer.duration
            property bool updatePosition:false

            property bool test:false
            value:audioPlayer.position
            //snapMode:
            stepSize: 1






            onValueChanged: {
                //audioPlayer.pause()
                //updatePosition=true
                audioPlayer.seek(value);
                //updatePosition=false
                //audioPlayer.play()
            }


        }
        Label{
            id:maxTime
            text:audioPlayer.isStopped ? "--/--" : msToTime(audioPlayer.duration);


        }
    }


    Item{

        width:parent.width
        height:row.height
        Row{
            id:row
            spacing:20
            anchors.centerIn: parent
            RoundButton{
                id:backward
                icon.source: !style.icon_pack_reset ? "image://icons/media-playback-back": ""
                display:Button.IconOnly
                width:window.state !==0 ? window.height*0.10:window.height*0.15
                height:width
                icon.width: width/2
                icon.height: height/2
                onClicked: {
                    playList.previousSong()
                }
            }
            RoundButton{
                id:play
                width:backward.width
                height:width
                icon.source: !style.icon_pack_reset ?
                                 "image://icons/media-playback-"+(audioPlayer.isPlaying?
                                                                      "pause":"start"): ""
                display:Button.IconOnly
                icon.width: width/2
                icon.height: height/2
                onClicked: {
                    if(audioPlayer.isPlaying){
                        audioPlayer.pause()

                    }else{
                        audioPlayer.play()
                    }
                }
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
                    playList.nextSong()
                }
            }
        }
    }




}
