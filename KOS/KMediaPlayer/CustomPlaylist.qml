import QtQuick 2.0

Item {
    id:item
    property alias playListModel: playListRepater.model
    property int currentIndex: -1


    onCurrentIndexChanged: {

        if(currentIndex === -1 || currentIndex >=playListRepater.count) return

        window.audioPlayer.source = playListRepater.itemAt(currentIndex).source
        window.audioPlayer.play();

    }


    Repeater{
        id:playListRepater
        delegate: Item{
            property string source:fileUrl
        }
    }
    function stop(){
        item.currentIndex = -1;
        audioPlayer.isStopped = true
        audioPlayer.stop()
        audioPlayer.source = ""
    }

    function nextWithoutAutoReturn(){
        var index =item.currentIndex;
        if(index < 0 ){stop();return;}
        item.currentIndex = index < playListRepater.count-1 ? index+1 : -1
    }

    function nextSong(){
        var index =item.currentIndex;
        if(index < 0 )return false;
        item.currentIndex = index < playListRepater.count-1 ? index+1 : 0
        return true
    }
    function previousSong(){
        var index =item.currentIndex;
        if(index < 0 )return false;
        item.currentIndex = index > 0 ? index-1 : playListRepater.count-1
        return true;
    }

}
