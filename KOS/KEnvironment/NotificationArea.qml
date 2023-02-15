import QtQuick 2.15
import QtQuick.Controls 2.15
import NotificationModel 1.0
import Notifications 1.0
SwipeView {

    id:swipe
    Component.onCompleted: {
        swipe.contentItem.highlightMoveDuration = 0
    }

    Connections{
        target:dropDownMenu
        function onClosed(){

            swipe.currentIndex = 1

        }
    }
    currentIndex:1
    orientation: Qt.Vertical
    onCurrentIndexChanged: {
        if(currentIndex == 0){
            if(!dropDownMenu.visible)
               dropDownMenu.open();
        }else{
           dropDownMenu.close();
        }
    }


    Item{width:1;height:1}
    ListView{

        id:view
        visible:swipe.currentIndex === 1
        orientation: ListView.Horizontal
        model:NotificationModel{list:notifyList}
        delegate:Button{
            width:48
            height:width
            icon.source: !style.icon_pack_reset ? "image://icons/"+appName : ""
            display:Button.IconOnly
        }

    }

}
