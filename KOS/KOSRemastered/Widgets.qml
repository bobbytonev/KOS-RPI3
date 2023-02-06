import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtWayland.Compositor 1.15
import WindowManager 1.0
ScrollView {

    id:scrollView
    visible:!dropDownMenu.visible && !shortcuts.visible && !trayDropDown.visible
    ScrollBar.horizontal.interactive:false
    contentWidth: window.homeScreen ? widgetLayout.width :
                                      window.width


    function maximize(wState,wMaximized,pid,index){
        manager.changeState(wState,pid);
        fullScreenVariable = wMaximized
        scrollView.contentItem.contentX=0
        widgetLayout.animationIndex =index
        window.homeScreen=false
        widgetLayout.selectedIndex=index


    }

    Connections{
        target:window
        function onWindowCreated(){
            widgetLayout.selectedIndex = window.shellSurfaces.count-1
            widgetLayout.animationIndex =widgetLayout.selectedIndex
            dropDownMenu.visible=false
            trayDropDown.visible=false

        }
        function onHome(){
            widgetLayout.animationIndex = widgetLayout.selectedIndex
            widgetLayout.selectedIndex = -1
        }
        function onBack(){
            if(scrollView.visible && !window.homeScreen)
                manager.back(windows.itemAt(widgetLayout.selectedIndex).windowPid);

        }

    }

    WindowManager{
        id:manager
        onFullScreen:(pid) => {

                         for(var i=0;i<windows.count;i++){

                             if(windows.itemAt(i).windowPid === pid){
                                 /*
                                 manager.changeState(2,pid);
                                 fullScreenVariable = true
                                 scrollView.contentItem.contentX=0
                                 widgetLayout.animationIndex =i
                                 window.homeScreen=false
                                 widgetLayout.selectedIndex=i
                                */
                                 scrollView.maximize(2,true,pid,i);
                                 break;
                             }
                         }


                     }
        onMaximized: (pid) =>{

                         for(var i=0;i<windows.count;i++){

                             if(windows.itemAt(i).windowPid === pid){
                                 /*
                                 manager.changeState(1,pid);
                                 fullScreenVariable = false
                                 scrollView.contentItem.contentX=0
                                 widgetLayout.animationIndex =i
                                 window.homeScreen=false
                                 widgetLayout.selectedIndex=i
                                */
                                 scrollView.maximize(1,false,pid,i);


                                 break;
                             }
                         }
                     }
    }


    Row{
        id:widgetLayout
        spacing:window.homeScreen ? 5:0
        x:window.homeScreen ? 0 : window.width * -selectedIndex
        property int selectedIndex: -1
        property int animationIndex: -1
        property bool removeAnimation: false
        move:Transition{
            SequentialAnimation{
                NumberAnimation{property: "x";duration:widgetLayout.removeAnimation ? 200:0}
                ScriptAction{script: widgetLayout.removeAnimation = false}
            }
        }

        Repeater{
            id:windows
            model:window.shellSurfaces
            delegate:Item{
                id:widgetSurface
                height: window.height

                property real itemWidth:{
                    switch(modelData.iviId % 10){
                    case 1:
                        return 1.5;
                    case 2:
                        return 2.5;
                    default:
                        return 3;
                    }
                }
                width:window.homeScreen
                      ? window.width/itemWidth :window.width
                property int windowPid: modelData.iviId





                Item{
                    //Pane{
                    property bool firstRun :true
                    id:windowBackground
                    Pane{

                        //Pane{
                        anchors.fill: parent
                        background:Rectangle{
                            color:!window.homeScreen ?  "transparent":"#64000000"
                            radius:20
                        }
                    }

                    anchors.centerIn: parent
                    height: window.homeScreen? window.height/1.7 :parent.height

                    width:parent.width



                    Behavior on width{
                        NumberAnimation{
                            duration:heightAnimation.duration
                            easing.type: Easing.InOutQuad
                        }
                    }
                    Behavior on height{
                        SequentialAnimation{
                            ScriptAction{script:{waylandWindow.opacity = 0}}
                            NumberAnimation{
                                id:heightAnimation
                                duration:widgetLayout.animationIndex !== index ? 0:200
                                // duration:200
                                easing.type: Easing.InOutQuad
                            }
                            ScriptAction{script:{waylandAnimation.stop();waylandAnimation.start()}}
                        }
                    }


                    WaylandQuickItem{
                        id:waylandWindow
                        anchors.fill: parent
                        visible:true
                        opacity:1
                        surface: modelData.surface
                        onSurfaceDestroyed:{
                            destroyAnimation.start()

                        }

                        NumberAnimation{
                            id:waylandAnimation
                            duration:100
                            target:waylandWindow
                            property:"opacity"
                            //easing.type: Easing.InOutQuad
                            from:0
                            to:1


                        }


                        SequentialAnimation{
                            id:destroyAnimation
                            NumberAnimation{target:widgetSurface;property:"scale";from:1;to:0;duration:200}
                            ScriptAction{script:{
                                    window.homeScreen=true
                                    widgetLayout.removeAnimation=true
                                    window.shellSurfaces.remove(index);


                                }
                            }
                        }
                        Connections{
                            target:window
                            function onHomeScreenChanged(){

                                if(window.homeScreen){
                                    manager.changeState(0,modelData.iviId);

                                    modelData.sendConfigure(Qt.size(window.width/itemWidth,window.height/1.7))
                                }else{
                                    if(widgetLayout.animationIndex !==index) return;



                                    if(!fullScreenVariable){

                                        manager.changeState(1,modelData.iviId);
                                    }
                                    modelData.sendConfigure(Qt.size(window.width,window.height))

                                }
                                // animation.start()
                                //waylandWindow.opacity = 1

                            }
                        }

                    }
                    RoundButton{
                        id:control
                        width:window.height * 0.07
                        height:width
                        icon.source: !style.icon_pack_reset ? "image://icons/app-close" : ""
                        //icon.source: !style.icon_pack_reset ? "image://icons/edit-delete-remove" : ""

                        x:parent.width-(width+y)
                        y:10
                        visible:window.homeScreen
                        onClicked:{
                            modelData.surface.client.close();



                        }

                    }


                }
            }

        }



    }




}
