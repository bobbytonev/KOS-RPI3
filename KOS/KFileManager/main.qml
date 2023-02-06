import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import WindowManager 1.0
import KFileManager 1.0
import QtQuick.VirtualKeyboard 2.2

ApplicationWindow {
    visible: true
    id:window
    width:1024
    height:600


    property alias stackView: stackView
    property int state:1
    property alias manager: manager
    property alias fileManager: fileManager
    property real headerHeight:0

    property real keyboardHeight
    signal activeChanged(bool active)



    KFileManager{
        id:fileManager
    }




    WindowManager{
        id:manager
        onBackClicked: {
            if(stackView.children.length < 2) {
              Qt.callLater(Qt.quit)
            }
        }
        onStateChanged: (state)=>{
                            if(window.state !==state){
                                window.state = state;
                                if(state === 0&&!minimizedImage.active ){

                                    minimizedImage.active = true
                                }
                            }
                        }

    }
    Loader{
        id:keyboardLoader
        //active:true
        //asynchronous: true
        z:99
        source:"Keyboard.qml"
    }
Loader{
    z:101
    id:minimizedImage;
    //asynchronous: true
    active:false
    anchors.fill: parent
    source:"MinimizedImage.qml"
    visible:window.state === 0


}

    StackView{
        id:stackView
        visible:!minimizedImage.visible
        anchors.fill: parent
    }
    Component.onCompleted: {

        // window.stackView.push("storage.qml",{startingFolder:moutingPoint})
        //stackView.push("main-page.qml")
        if(window.header !=undefined){
            headerHeight = window.header.height
        }
        keyboardLoader.active=true
         if(folderPath.length > 0){
             window.stackView.push("storage.qml",{startingFolder:folderPath})
         }else{
            stackView.push("main-page.qml")
         }

    }

}
