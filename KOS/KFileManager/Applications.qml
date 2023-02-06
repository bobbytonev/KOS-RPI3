import QtQuick 2.0
import QtQuick.Controls 2.15
import AppStarter 1.0
Popup {
    id:pop
    property string path
    visible:false
    modal:true
    AppStarter{
        id:appStarter;
        active:true
        onLoadEnded:(result)=> {
                        if(!result) pop.close()
                    }
    }
    BusyIndicator{
        anchors.centerIn: parent
        visible:appStarter.state === 1

    }
    onOpened: {
        appStarter.startApplication(pop.path)
    }

    Connections{
        target:appLoader
        function onFileClicked(filePath){

            pop.path = filePath

            pop.open();



        }
    }

    ListView{
        id:view
        anchors.fill: parent
        model:appStarter
        spacing:5
        delegate:Button{
            text:name
            icon.source: !style.icon_pack_reset ? "image://icons/"+appIcon:""
            width:view.width
            height:window.height*0.12
            onClicked: {
                var args = ["file:///"+pop.path]
                appLauncher.start(appPath,args);
                pop.close()
            }
        }

    }




}
