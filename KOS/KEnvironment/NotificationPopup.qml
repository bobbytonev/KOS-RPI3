import QtQuick 2.15
import QtQuick.Layouts 1.15
import NotificationModel 1.0
import Notifications 1.0
StackLayout{
    width:parent.width/2
    id:stackLayout

    Connections{
        target:dropDownMenu
        function onOpened(){
            stackLayout.visible=false

        }
        function onClosed(){

            stackLayout.visible=true
        }
    }



    Repeater{
        id:notifyModel
        model:NotificationModel{list:notifyList}
        onCountChanged:{
            stackLayout.currentIndex = notifyModel.count-1
        }

        delegate:Item{
            width:stackLayout.width
            Layout.preferredHeight:notifyItem.height


            //0 - Low - noPoup , can be removed
            //1 - Normal - popup , can be removed
            //2 - Medium - noPopup , cant be removed
            //3 - High - popup ,cant be removed
            //4 - Ultra - stickyPopUp, cant be removed
            Notification{
                y:-height


                NumberAnimation on y{
                    id:animation
                    from:-height
                    to:0
                    running:false
                    duration:250
                    //easing.type:Easing.OutBounce
                    easing.type:Easing.OutQuad
                }




                visible:priorityId > 0 && priorityId !==2


                enabled:visible
                Connections{
                    target:notifyList
                    function onNotificationChanged(notifyIndex){
                        if(notifyIndex === index){
                            stackLayout.currentIndex = index //brint to front
                            if(notifyItem.y !== 0){ //pop in animation


                                animation.from=notifyItem.y
                                animation.to = 0
                                animation.duration= 250
                                animation.start()
                                timer.restart()

                            }

                        }
                    }
                }
                Component.onCompleted: {
                    animation.start()

                }

                onOpacityChanged: {

                    if(opacity === 0){
                        notifyList.removeItemAt(index);
                    }
                }
                Timer{
                    id:timer
                    interval:priority > 2 ? 30000 : 6000
                    running:notifyItem.timerRunning
                    onTriggered: {
                        animation.to=-height
                        animation.from=0
                        animation.duration = 100
                        animation.start()
                        // notifyItem.visible = false

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
                menus:buttons


            }
        }

    }

}


