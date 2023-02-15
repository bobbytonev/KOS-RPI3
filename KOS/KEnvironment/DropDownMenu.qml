import QtQuick 2.15
import QtQuick.Controls 2.15
import NotificationModel 1.0
import Notifications 1.0
import QtQuick.Layouts 1.15
Popup {

    Label{
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text:qsTr("No new notifications");
        visible:view.count  === 0
    }




    onOpened: {
        window.backButton = true
    }
    onClosed: {
        if(window.homeScreen)
            window.backButton = false
    }
    ListView{
        id:view
        width:parent.width/2
        height: parent.height
        anchors.centerIn: parent

        orientation: ListView.Vertical
        spacing:20
        add:Transition {
            NumberAnimation{property: "scale";to:1;from:0;duration:200}

        }
        addDisplaced: Transition {
            NumberAnimation { property: "y"; duration: 200 }
        }
        model:NotificationModel{list:notifyList}
        delegate:Item{
            width:view.width
            height:notifyItem.height

            Notification{
                onOpacityChanged: {
                    if(opacity === 0){
                        notifyList.removeItemAt(index);
                    }
                }


                id:notifyItem
                aName:appName;
                iPath:imagePath
                nId:notifyId
                customQml:qmlLoaderPath
                priorityId:priority
                appImage:!style.icon_pack_reset ? "image://icons/"+appName : ""
                nTitle:title
                notifyImage:!imageProvider ? imagePath :
                                             !style.icon_pack_reset ? "image://icons/"+imagePath : ""
                bodyLabel:bodyText
                menusSize:buttons.length
                menus:buttons




            }

        }

        header:Item{
            width:parent.width
            height:column.height
            Column{
                id:column
                anchors.centerIn: parent
                spacing:10
                width:parent.width/2
                PowerButtons{}
                //VolumeSlider{}
                //BrightnessSlider{}



            }
        }


    }

}
