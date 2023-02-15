import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2
import SystemApplications 1.0
Item{
    id:item1;
    property bool appStart:false
    Connections{
        target:window
        function onWindowCreated(){

            shorcutsPopup.close();

        }
    }
    onVisibleChanged: {
        appStart = false
    }



    //ScrollView {

    //topPadding: window.width*7/100
    //id: scrollView


    //anchors.centerIn: parent

    //height: item1.height


    //ScrollBar.horizontal.policy:ScrollBar.AlwaysOff
    //clip:false
    Image{
        id:appLoader
        anchors.centerIn: parent
        scale:appStart ? 1:0
        visible:appStart
        Behavior on scale{
            NumberAnimation{duration:200;easing.type:Easing.InOutQuad}
        }


        //onSourceChanged: {
          //  scale = 1
        //}
    }
    BusyIndicator{
        id:loadingIndicator
        running:true
        anchors.centerIn: parent
    }



    GridView{
        id:grid
        visible:!appStart
        property real spacing: item1.height * 0.01
        topMargin: window.width*7/100
        width:(cellWidth+spacing)*4
        height:parent.height
        //visible:appLoading
        //x:parent.width/2-width/2
        anchors.centerIn: parent
        cellWidth:item1.height *settings.appsIconSize +spacing
        cellHeight:cellWidth

        //Grid{
        //  id:grid


        //spacing: item1.height * 0.01
        //columns: 5
       // populate: Transition{NumberAnimation{property:"scale";from:0;to:1;duration:200}}
        add:Transition{NumberAnimation{property:"scale";from:0;to:1;duration:200}}
        remove:Transition{NumberAnimation{property:"scale";from:1;to:0;duration:200}}
        // Repeater{
        //   id:buttonRepeater
        model:Applications{
            language:lang.language;id:appsModel
            onLanguageChanged: {
                active=true
            }
            onLoadingChanged: {
                if(!loading){
                    loadingIndicator.running=false

                }
            }

        }
        delegate:Button{
            id:control
            height: grid.cellWidth -grid.spacing //item1.height *settings.appsIconSize
            //  height:item1.height * 0.30
            width: height
            // scale:0
            icon.source: !style.icon_pack_reset ? "image://icons/"+appIcon : ""
            icon.cache: false
            display: settings.iconText ? Button.TextUnderIcon : Button.IconOnly
            text:name
            onClicked:{
               //< appLoader.scale = 0
                appLoader.source = icon.source
                appStart = true
                appLauncher.start(appPath)

            }



        }
        // }
        //}

    }







}
