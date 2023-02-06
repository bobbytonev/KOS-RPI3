import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtWayland.Compositor 1.2

import QtQuick.VirtualKeyboard 2.15


WaylandCompositor {
    id: qmlCompositor



    WaylandOutput {
        compositor: qmlCompositor
        id: qmlOutput
        window: ApplicationWindow {
            width: 1024
            height: 600
            visible: true
            id:window
            color:"black"

            signal home();
            signal back();
            signal windowCreated();


            property bool homeScreen: true
            property bool backButton: false
            property alias shellSurfaces: shellSurfaces
            property alias launcher: launcher

            onHome:{
                homeScreen = true
            }

            header:Item{height:0}
            footer:Item{height:0}



            Loader{
                id:launcher
                anchors.fill: parent
                source:themeData.Launcher === undefined ? "Launcher.qml" : themeData.Launcher[1]
                active: true
                onStatusChanged: {
                    if(status == Loader.Ready){
                        stopAnimation;
                    }
                }

            }



        }//window



    }//output





    ListModel{id: shellSurfaces}
    IviApplication{
        onIviSurfaceCreated: {

            console.log(iviSurface.iviId);
            //window.homeScreen=false
            shellSurfaces.append({shellSurface:iviSurface})
            if(iviSurface.iviId %10 === 1){
                shellSurfaces.move(shellSurfaces.count-1,0,1);
            }

            iviSurface.sendConfigure(Qt.size(window.width,window.height))
            window.windowCreated()
            window.homeScreen=false

        }
    }
}
