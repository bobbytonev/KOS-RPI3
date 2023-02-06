import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

RowLayout{


    Item{
        Layout.fillHeight: true
        Layout.fillWidth: true
        Image{
            width:32
            height:32
            anchors.centerIn: parent
            source: !style.icon_pack_reset ? "image://icons/audio-cover": ""

        }
    }
    Label{
        Layout.fillWidth: true
        text:window.audioPlayer.songTitle
    }
    RoundButton{
        id:backward
        icon.source: !style.icon_pack_reset ? "image://icons/media-playback-back": ""
        display:Button.IconOnly
        Layout.preferredWidth: window.height*0.10
        Layout.preferredHeight: width
        icon.width: width/2
        icon.height: height/2
        onClicked: {
            playList.previousSong()
        }
    }
    RoundButton{
        id:play
        Layout.preferredWidth: window.height*0.12
        Layout.preferredHeight: width
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
        Layout.preferredWidth: window.height*0.10
        Layout.preferredHeight: width
        icon.source: !style.icon_pack_reset ? "image://icons/media-playback-next": ""
        display:Button.IconOnly
        icon.width: width/2
        icon.height: height/2
        onClicked: {
            playList.nextSong()
        }
    }


}


