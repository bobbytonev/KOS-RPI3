import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import SystemClock 1.0
Item{
    id:item

    height:parent.height

    SystemClock{
        id:sysClock
    }

    function setAppTime(){
        var today = new Date();
        var format =sysClock.apFormat ? "ap" : ""
        var s =Qt.formatDateTime(new Date(),"hh:mm"+format);


            time.text =s;
        }

    Label{
        anchors.centerIn: parent
        padding: 0
        id:time
        color:"white"
        leftPadding: 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        height:32
        font.pixelSize: 20
        property bool dropDownMenuOpenned: false
        Behavior on font.pixelSize{
            NumberAnimation{
                duration:100

            }
        }

        Connections{
            target:dropDownMenu
            function onOpened(){


                time.font.pixelSize = 26
                time.dropDownMenuOpenned = true


            }
            function onClosed(){


                time.font.pixelSize = 20
                time.dropDownMenuOpenned=false

            }
        }

        Timer{
            id:timer
            interval: 500; running:true ; repeat: true
            onTriggered: {

                item.setAppTime();
            }

        }

    }
}
