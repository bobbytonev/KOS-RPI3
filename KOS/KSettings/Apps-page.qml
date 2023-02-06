import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.5

Item {


    BusyIndicator{
        //running:appsLoader.status === Loader.loading
        //      || defaultApps.status === Loader.loading
        //    || extendedDefaultApps.status === Loader.loading
        running:defaultApps.status === Loader.loading
                ||extendedDefaultApps.status === Loader.loading

        anchors.centerIn: parent
    }

    SwipeView {
        id: swipeView
        height: parent.height
        anchors.fill: parent
        //clip:true
        anchors.topMargin: tabBar.height
        currentIndex: tabBar.currentIndex

        onCurrentIndexChanged: {


            if(currentIndex===1&&!defaultApps.active){

                defaultApps.active=true
            }else if(currentIndex===2&&!extendedDefaultApps.active){
                //if(!appsLoader.active)appsLoader.active=true
                extendedDefaultApps.active=true

            }
        }
//Component.onCompleted:{allApps.active = true}
	//Connections{
	 // target:pageView
	  //function onBusyChanged(){
		//console.log(pageView.busy);
		//if(!allApps.active && !pageView.busy) allApps.active = true
	
	 // }
	//}
       

	// Loader{
           // asynchronous: true
          //  active:false
            //id:allApps
            //source:"AllApps.qml"
        //}
        
       AllApps{}
        Loader{
            property bool isExtended: false
            id:defaultApps
           // asynchronous: true
            active:false
            source:"DefaultApps.qml"


        }

        Loader{
            property bool isExtended: true
            id:extendedDefaultApps
           // asynchronous: true
            active:false
            source:"DefaultApps.qml"


        }






    }

    TabBar {
        id: tabBar
        //y: parent.height-tabBar.height
        //anchors.topMargin: swipeView.height
        width: parent.width
        position: TabBar.Footer
        currentIndex: swipeView.currentIndex
        background: Rectangle{
            color:"transparent"
        }


        TabButton {
            text: qsTr("All Apps")

        }

        TabButton {
            text: qsTr("Default Apps")

        }
        TabButton {
            text: qsTr("Extended Default Apps")

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
