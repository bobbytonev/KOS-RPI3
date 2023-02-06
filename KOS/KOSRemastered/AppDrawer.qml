import QtQuick 2.0
import QtQuick.Controls 2.12
Item{
    id:item
    visible:window.homeScreen && !window.backButton
    Connections{
        target:shortcuts
        function onClosed(){
            //swipe.currentIndex = 0

            item.y =yMax
        }

    }
    property real yMax: window.height-height


    Image{
        id:appDrawerImage
        width:parent.height/3
        height:width
       // visible:window.homeScreen && !window.backButton
        anchors.centerIn: parent
        source:!style.icon_pack_reset ? "image://icons/app-drawer" : ""
        cache:false

    }
    opacity:1-(yMax-y)/150
    onYChanged: {
        if(y === (yMax-150)){
            shortcuts.open()
        }
    }


    NumberAnimation{
        id:returnAnimation
        duration:200
        running:false
        property: "y"
       // easing.type: Easing.InOutElastic
        easing.type: Easing.InOutQuad
        target:item

    }

    MouseArea{
        id:mouse
        anchors.fill: parent
        drag.target: item
        drag.axis: Drag.YAxis
        drag.maximumY:yMax
        drag.minimumY:yMax-150
        onReleased: {
            var toVar ;

            if((yMax-parent.y)>50) toVar = yMax-150;

            else toVar =yMax


            returnAnimation.to = toVar
            returnAnimation.from = parent.y
            returnAnimation.running = true

        }
    }

    /*
    SwipeView {
        id:swipe
        visible:appDrawerImage.visible
        anchors.fill: parent
        orientation:Qt.Vertical
        Item{}
        Item{}
        Component.onCompleted: {
             swipe.contentItem.highlightMoveDuration = 0
        }

        onCurrentIndexChanged: {
           if(currentIndex === 1) { shortcuts.open();}
        }


    }
    */

}
