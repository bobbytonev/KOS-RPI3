import QtQuick 2.0

Item {
    id:item
    property alias playListModel: playListRepater.model
    property int currentIndex: -1


    onCurrentIndexChanged: {

        if(currentIndex === -1 || currentIndex >=playListRepater.count) return

        window.mediaPlayer.source = playListRepater.itemAt(currentIndex).source
        window.mediaPlayer.play();

    }


    Repeater{
        id:playListRepater
        delegate: Item{
            property string source:fileUrl
        }
    }
    function stop(){
        item.currentIndex = -1;
        mediaPlayer.isStopped = true
        mediaPlayer.stop()
        mediaPlayer.source = ""
    }

    function nextVideo(){
        var index =item.currentIndex;
        if(index < 0 )return;
        item.currentIndex = index < playListRepater.count-1 ? index+1 : 0
    }
    function previousVideo(){
        var index =item.currentIndex;
        if(index < 0 )return;
        item.currentIndex = index > 0 ? index-1 : playListRepater.count-1
    }

}
