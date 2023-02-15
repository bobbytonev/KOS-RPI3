import QtQuick 2.15
import QtQuick.Controls 2.15
import DefApps 1.0
Item{
    id:item
    property bool extended: parent.isExtended


    Connections{
        target:manager
        function onStateChanged(state){
            if(state === 0){
                ///  appInfo.close()
                /// mimetypes.close();
                appDialog.close()
            }
        }
    }

    ApplicationDialog{
        id:appDialog
        modal:true
        appFilterCategory:extended ?"mimetypes" :"category"
        onAppClicked:(appConfig,appPath,appIcon)=> {
                         defApps.changeData(buttonIndex,appConfig,appPath,appIcon)
                     }
        onAppRemoved: {
            Qt.callLater(defApps.remove,buttonIndex);
        }


    }

    /*

    Popup{
        id:appInfo
        width:parent.width
        height:parent.height
        onOpened: {
            if(!loader.active)loader.active=true
        }
        onVisibleChanged: {
            parent.visible=!appInfo.visible
        }


        Connections{
            target:window
            function onBackButtonClicked(){
                if(appInfo.visible){
                    window.block = true
                    appInfo.close();

                }

            }
        }
        Loader{
            anchors.fill: parent
            id:loader
            property string appFilter
            property string appFilterName:item.parent.isExtended ?"mimetypes" :"category"
            property var button
            property var popup:appInfo

            active:false
            source:"DefaultAppsContent.qml"

        }

    }




    Mimetypes{
        id:mimetypes
        onMimeType:(name)=>{
                       defApps.add(name);
                   }

    }
*/
    Loader{
        anchors.fill: parent
        property bool requestOpen:false
        signal mimeType(string name,string suffix)
        id:mimetypesLoader;
        source:"Mimetypes.qml"
        active:extended
        onMimeType: (name,suffix)=>{
                        defApps.addItem(name,suffix);
                    }
    }





    ListView{
        id:view
        anchors.fill: parent
        model:DefaultApplications{id:defApps;language:lang.language;extended:item.extended}
        delegate:Button{
            height:window.height*0.12
            // property var appName
            // property var appIcon
            // property var appPath
            // property var appConf
            //onAppNameChanged: {
            //  name =appName
            // defAppIcon=appIcon
            // defAppPath=appPath
            // config=appConf

            // if(appName ===""&&defApps.extended) //remove from settings
            //   defApps.remove(index);
            //else
            //  defApps.saveToSettings(index);


            //}

            width:view.width
            text:qsTr(category)+": "+name
            icon.source: defAppIcon.length > 0&&!style.icon_pack_reset ? "image://icons/"+ defAppIcon:""
            id:control

            onClicked:{
                appDialog.appFilter = !extended ? category : mimetype
                appDialog.buttonIndex = index
                appDialog.open();
                //loader.button=control
                //loader.appFilter=!isExtended ?category : mimetype


                //appInfo.open();
            }

        }
        footer:Column{
            width:parent.width

            MenuSeparator{
                width: parent.width
                visible:extended
            }
            Button{
                width:parent.width
                height:window.height*0.12
                text:item.parent.isExtended? qsTr("Add") :""
                visible:extended
                onClicked:{

                    //mimetypes.open();
                    mimetypesLoader.requestOpen = true
                    mimetypesLoader.active=true
                }
            }
        }

    }



}
