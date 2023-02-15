import QtQuick 2.15
import QtQuick.Controls 2.15
import TrayIconModel 1.0
import TrayIcon 1.0
import QtQuick.Layouts 1.15
Popup {
    id:pop
    onOpened: {
        window.backButton = true
    }
    onClosed: {
        if(window.homeScreen)
            window.backButton = false
    }

    Popup{
        id:contextMenu
        property var list:[]
        property string trayAppName
        property int trayNumber
        x:parent.width/2-width/2
        y:parent.height/2 - height/2
        width:parent.width/3
        //height:width
        contentItem:Item{
            Pane{anchors.fill: parent}
            ListView{
                clip:true
                id:popView
                anchors.fill: parent
                model:contextMenu.list.length
                delegate:Button{
                    text:contextMenu.list[index]
                    width:popView.width
                    height:window.height*0.10
                    onClicked: {
                        trayList.sendContextMenuSignal(index,"MClicked",contextMenu.trayAppName,contextMenu.trayNumber);
                        contextMenu.close()
                    }

                }
            }
        }
        onAboutToShow: {
            scrollView.visible=false
        }
        onClosed: {
            scrollView.visible=true
        }
    }

    ScrollView {

        id: scrollView
        anchors.centerIn: parent
        width:parent.width/2
        height: parent.height
        ScrollBar.horizontal.policy:ScrollBar.AlwaysOff
        clip:false
        Behavior on scale{
            NumberAnimation{duration:100}
        }


        Grid{
            id:grid


            spacing: parent.height * 0.08
            columns: 5
            move:Transition{
                NumberAnimation{properties:"x,y";duration:400;easing.type: Easing.InOutQuad}
            }


            Repeater{
                id:buttonRepeater


                model:TrayIconModel{list:trayList;id:iconModel}

                delegate: Item{
                    id:item
                    property int isChecked: trayId/100%10
                    property int textVisibility: trayId/10%10
                    property int visibility: trayId%10
                    property bool firstRun:true
                    width:window.height*0.22
                    height:width
                    state:visibility!==1 ? "Visible" : "Invisible"
                    Component.onCompleted: {
                        if(visibility!==1&&pop.visible){
                            animation.start();
                        }
                    }

                    NumberAnimation{
                        id:animation
                        from:0
                        to:1
                        target:item
                        duration:300
                        easing.type: Easing.InOutQuad
                        property: "scale"
                    }

                    states:[
                        State {
                            name: "Invisible"
                            PropertyChanges {target: item;scale:0}
                            PropertyChanges {target: item;visible:false}
                        },State{
                            name: "Visible"
                            PropertyChanges {target: item;visible:true}
                            PropertyChanges {target: item;scale:1}

                        }


                    ]
                    transitions: [
                        Transition {
                            from: "Visible"
                            to: "Invisible"
                            SequentialAnimation{
                                NumberAnimation{
                                    duration:pop.visible ? 200:0
                                    target:item
                                    property: "scale"
                                }
                                NumberAnimation{
                                    duration:0
                                    target:item
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
                                    target:item
                                    property: "visible"
                                }
                                NumberAnimation{
                                    // duration:pop.visible ? 300:0
                                    duration:200
                                    //easing.type: Easing.InOutQuad
                                    target:item
                                    property: "scale"
                                }

                            }
                        }



                    ]

                    Pane{
                        id:background
                        width:control.width
                        height:control.height
                        opacity:item.isChecked !==0 ? 1: 0
                       // scale:control.down ? 1.1: 1

                        Behavior on opacity{
                            NumberAnimation{
                                duration:  200
                            }
                        }

                    }



                    Button{

                        scale:control.down ? 1.2:1
                        Behavior on scale{
                            NumberAnimation{
                                duration:  200
                                easing.type: Easing.InOutQuad
                            }
                        }

                        id:control
                        width:parent.width


                        height:width
                        icon.source: !imageProvider ? imagePath :
                                                      !style.icon_pack_reset ? "image://icons/"+imagePath : ""
                        text:item.textVisibility === 1 ? "": bodyText
                        display:text.length === 0 ? Button.IconOnly :
                                                    imagePath.length === 0 ? Button.TextOnly : Button.TextUnderIcon

                        font.pixelSize: height * 0.13
                        background:Item{


                        }
                        onClicked: {

                            trayList.sendSignal("Clicked",appName,trayId)
                        }
                        onPressAndHold: {
                            if(menus.length > 0){
                                contextMenu.trayAppName = appName
                                contextMenu.trayNumber = trayId
                                contextMenu.list = menus
                                contextMenu.open()
                            }else{
                                trayList.sendSignal("LongPress",appName,trayId)
                            }
                        }


                    }

                }

            }
        }


    }

}
