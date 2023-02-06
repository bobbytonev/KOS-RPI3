import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15
Item{


    property var settingsNames: [qsTr("Wi-Fi"),qsTr("Bluetooth"),qsTr("Appearance"),
        qsTr("Apps"),qsTr("Audio"),qsTr("System")]

    property var settingsPages: ["Wi-Fi","Bluetooth","Appearance",
        "Apps","Audio","System"]


    Flow {
        id: grid
        anchors.fill: parent
        Repeater{
            id:rep
            model:settingsNames.length
            Button{
                id:control
                text:settingsNames[index];
                width:parent.width/3
                height: window.height*0.21
                onClicked: {
                    window.pageView.push(settingsPages[index]+"-page.qml");

                }

                icon.source: !style.icon_pack_reset ? "image://icons/settings-"+settingsPages[index]: ""
            }

        }
    }
}

