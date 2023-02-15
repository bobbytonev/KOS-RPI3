import QtQuick 2.15
import QtQuick.Controls 2.15
Popup{
    id:shorcutsPopup
    visible:false


    BusyIndicator{
        anchors.centerIn: parent
        visible:shortcuts.status == Loader.Loading || shortcuts.status == Loader.Loading
                || backgroundLoader.status == Loader.Loading
    }


    onOpened: {
        if(!shortcuts.active)  shortcuts.active = true

        window.backButton = true
    }
    onClosed: {
        if(window.homeScreen)
            window.backButton = false


    }
    Connections{
        target:lang
        function onLanguageChanged(language){
            shortcuts.active=false
        }
    }

    SwipeView{
        id:swipe
        anchors.fill: parent
        currentIndex: 1

        onCurrentIndexChanged: {

            if(currentIndex === 0 && !launcherSettings.active){
                launcherSettings.active = true
            }
        }

        Loader{
            id:launcherSettings
            active:false//true
            asynchronous: true
            visible:swipe.currentIndex === 0
            source:"LauncherSettings.qml"

        }

        Loader{
            id:shortcuts
            active:false
            source:"Shortcuts-Content.qml"
            asynchronous: true
            visible:status == Loader.Ready

        }
        Loader{
            id:backgroundLoader
            //asynchronous: true
            active:SwipeView.isCurrentItem//keeps ram low
            source:"BackgroundChooser.qml"


        }


    }

}
