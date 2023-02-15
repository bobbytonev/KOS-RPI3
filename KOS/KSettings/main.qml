import QtQuick 2.15
import QtQuick.Controls 2.15
import WindowManager 1.0
ApplicationWindow {
    id:window
    visible:true
    width: 1024
    height:600

    property int state:1
    property bool block: false
    signal backButtonClicked();
    property alias pageView:pageView
    property alias manager: manager
    property real keyboardHeight

    property real headerHeight:0

    signal activeChanged(bool active)

    Component.onCompleted: {
        if(page !=="")
            pageView.push(page,{load:true});
        else
            pageView.push("main-page.qml");

        if(window.header !=undefined){
            headerHeight = window.header.height


        }
        //keyboardLoader.active=true

    }


    Loader{
        id:keyboardLoader
        //active:true
        z:99
        //asynchronous: false
        source:"Keyboard.qml"
    }

    WindowManager{
        id:manager
        onBackClicked: {
            window.backButtonClicked();
            if(!window.block){
                if(pageView.children.length>1) {
                    pageView.pop();
                }else{
                    Qt.callLater(Qt.quit)
                }
            }
            window.block = false
        }
        onStateChanged:(state) =>{

                           if(window.state !==state){
                               window.state = state;

                               //if(state === 0&&!minImageLoader.active)
                               //minImageLoader.active=true

                               //if(state !==2){
                               //window.header.height = headerHeight
                               //}
                           }
                       }

    }


    Loader{
        z:101

        id:minImageLoader
        // active:false//window.state === 0
        active:true
        source:"MinimizedImage.qml"
        anchors.fill: parent
        visible:window.state === 0
    }


    StackView {
        id: pageView
        visible:!minImageLoader.visible
        anchors.fill: parent

    }



}

