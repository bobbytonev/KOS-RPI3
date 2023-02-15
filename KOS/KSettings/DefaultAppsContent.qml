import QtQuick 2.0
import AllApplications 1.0
import QtQuick.Controls 2.12
Item {
    Component.onCompleted: {
        allApps.active=true
    }

    ListView{
        id:view
        anchors.fill: parent
        model:AllApplications{id:allApps ;filter:loader.appFilter;filterName:loader.appFilterName}

        delegate:Button{
            height:window.height*0.12
            width:view.width
            text:name
            icon.source: !style.icon_pack_reset ? "image://icons/"+ appIcon:""
            onClicked:{

                loader.button.appIcon=appIcon;
                loader.button.appPath=appPath;
                loader.button.appConf=confPath


                loader.button.appName=text;



                loader.popup.close();

            }
        }
        footer:Column{
            width:parent.width
            MenuSeparator{
                width: parent.width
            }
            Button{
                width:parent.width
                height:window.height*0.12

                display:Button.IconOnly
                icon.source: !style.icon_pack_reset ? "image://icons/filemanager-delete":""
                onClicked:{
                    loader.button.appIcon="";
                    loader.button.appPath="";
                    loader.button.appName="";
                    loader.popup.close();
                }
            }
        }
    }


}
