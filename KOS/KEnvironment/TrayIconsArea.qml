import QtQuick 2.15
import QtQuick.Controls 2.15
import TrayIconModel 1.0
import TrayIcon 1.0
SwipeView {
    id:swipe
    currentIndex:1
    orientation: Qt.Vertical
    interactive: true

    Component.onCompleted: {
        swipe.contentItem.highlightMoveDuration = 0
    }
    onCurrentIndexChanged: {
        if(currentIndex == 0){
            if(!trayDropDown.visible)
                trayDropDown.open();
        }else{
            trayDropDown.close();
        }
    }

    Connections{
        target:trayDropDown
        function onClosed(){

            swipe.currentIndex = 1

        }
    }
    Item{width:1;height:1}

    ListView{

        id:view
        layoutDirection: Qt.RightToLeft

        visible:swipe.currentIndex === 1
        orientation: ListView.Horizontal
        remove:Transition {
            NumberAnimation{property: "scale";to:0;from:1;duration:200}

        }
        add:Transition {
            NumberAnimation{property: "scale";to:1;from:0;duration:200}

        }

        model:TrayIconModel{list:trayList}
        delegate:RoundButton{

            property int visibility: trayId%10
            property int textVisibility: trayId/10%10

            //opacity:visibility !=2 ? 1 : 0
            id:control
            state:visibility !=2 ? "Visible" : "Invisible"
            states:[
                State {
                    name: "Invisible"
                    PropertyChanges {target: control;scale:0}
                    PropertyChanges {target: control;width:0}
                    PropertyChanges {target: control;visible:false}
                },State{
                    name: "Visible"
                    PropertyChanges {target: control;visible:true}
                    PropertyChanges {target: control;width:control.implicitWidth}
                    PropertyChanges {target: control;scale:1}

                }


            ]
            transitions: [
                Transition {
                    from: "Visible"
                    to: "Invisible"
                    SequentialAnimation{
                        NumberAnimation{
                            duration:200
                            target:control
                            property: "scale"
                        }
                        NumberAnimation{
                            duration:0
                            target:control
                            property: "width"
                        }

                        NumberAnimation{
                            duration:0
                            target:control
                            property: "visible"
                        }
                    }
                },
                Transition {
                    from: "Invisible"
                    to: "Visible"
                    SequentialAnimation{
                        NumberAnimation{
                            duration:0
                            target:control
                            property: "visible"
                        }
                        NumberAnimation{
                            duration:0
                            target:control
                            property: "width"
                        }

                        NumberAnimation{
                            // duration:pop.visible ? 300:0
                            duration:200
                            //easing.type: Easing.InOutQuad
                            target:control
                            property: "scale"
                        }


                    }
                }



            ]


            height:view.height
            icon.source:!imageProvider ? imagePath :
                                         !style.icon_pack_reset ? "image://icons/"+imagePath : ""
            text:textVisibility !==2 ? bodyText:""
            display:text.length === 0 ? Button.IconOnly :imagePath.length === 0 ? Button.TextOnly : Button.TextBesideIcon

            onClicked: {
                trayList.sendSignal("Clicked",appName,trayId)
            }
            onPressAndHold: {
                if(menus.length > 0){
                    menu.open()
                }else{
                    trayList.sendSignal("LongPress",appName,trayId)
                }
            }

            Menu{
                id:menu
                scale:0
                onOpened: swipe.interactive = false
                onClosed: swipe.interactive = true
                Repeater{
                    model:menus.length
                    MenuItem{
                        text:menus[index]
                        onClicked: {
                            trayList.sendContextMenuSignal(index,"MClicked",appName,trayId);
                        }
                    }

                }
                enter:Transition {
                    NumberAnimation{property: "scale";to:1;from:0;duration:50}

                }


            }//menu
        }

    }

}
