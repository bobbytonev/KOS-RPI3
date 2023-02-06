import QtQuick 2.0
import AllApplications 1.0
import QtQuick.Controls 2.12
Popup {
    id:pop
    property string appFilterCategory
    property string appFilter
    property int buttonIndex
    signal appClicked(string appConfig,string appPath,string appIcon)
    signal appRemoved()

    onOpened: {
        if(!allApps.active)
            allApps.active = true
        //else
            //allApps.reset();
    }

    BusyIndicator{
        anchors.centerIn: parent
        running:allApps.running;
    }

    contentItem:ListView{
        id:view
        model:AllApplications{id:allApps ;language:lang.language;filter:appFilter;filterCategory:appFilterCategory}

        delegate:Button{
            height:window.height*0.12
            width:view.width
            text:name
            icon.source: !style.icon_pack_reset ? "image://icons/"+ appIcon:""
            onClicked:{
                appClicked(confPath,appPath,appIcon)
                close()
                //loader.button.appIcon=appIcon;
                //loader.button.appPath=appPath;
                ///loader.button.appConf=confPath


                //loader.button.appName=text;



                //loader.popup.close();

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
                    if(pop.parent.extended )
                        appRemoved();
                    else
                        appClicked("","","")

                    close();
                }
            }
        }
    }



}
