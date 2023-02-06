import QtQuick 2.0
import QtQuick.Controls 2.0
Item {

    property var buttonNames : [qsTr("Language"),qsTr("Date and clock"),qsTr("About")]
    property var pages : ["Languages","DateClock","About"]


    ListView{
        id:view
        anchors.fill: parent
        model:buttonNames.length
        delegate:Button{
            width: view.width
            text:buttonNames[index];
            height: window.height*0.12
            onClicked: {
                window.pageView.push(pages[index]+"-page.qml");

            }
        }

    }





}
