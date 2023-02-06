import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import BluetoothDevice 1.0
Item{
    id:item
    property string deviceName
    property alias deviceIcon:device.icon.source
    property alias devicePath: btDevice.devicePath
    signal play()
    signal pause()
    signal next()
    signal previous()


    MouseArea{
        anchors.fill: parent
        visible:window.state ===0
        onClicked:{
            window.manager.requestMaximized()
        }
    }

    GridLayout{
        id:grid
        anchors.fill: parent
        BluetoothDevice{
            id:btDevice
        }
        //  flow:window.state === 0 ? GridLayout.TopToBottom : GridLayout.LeftToRight
        // Item{width:32;height:1}

        state: window.state === 0 ? "Minimized":"Maximized"

        states: [//playerControls
            State{
                name:"Minimized"
                PropertyChanges {target:grid;flow:GridLayout.TopToBottom;}
                PropertyChanges{target:device;Layout.fillWidth: true}
                PropertyChanges{target:playerControls;
                    Layout.preferredWidth:parent.width
                    Layout.preferredHeight:row.height
                }
            },State{
                name:"Maximized"
                PropertyChanges {target:grid;flow:GridLayout.LeftToRight}
                PropertyChanges{target:device;Layout.fillWidth: false}
                PropertyChanges{target:playerControls;
                    Layout.preferredWidth:row.width
                    Layout.preferredHeight:grid.height
                }

            }



        ]
        //Item{Layout.preferredHeight: 1;Layout.preferredWidth: 32}
        RoundButton{
            id:device
            //Layout.fillHeight: true
            //  Layout.fillWidth: true
            // Layout.fillWidth: window.state === 0 ? true:false


            //height:parent.height
            //width:height
            //enabled: false
            //font.pixelSize: 12
            text:deviceName
           // onClicked: {
             //   if(window.state === 0 ){
               //     window.manager.requestMaximized()
                //}
            //}

        }


        Label{
            id:title

            //height:parent.height
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            // width:parent.width -(device.width+62+backward.width*4)
            text:btDevice.title
        }

        Item{
            id:playerControls
            Layout.preferredWidth:parent.width
            Layout.preferredHeight:row.height
            Row{
                id:row
                anchors.centerIn: parent
                RoundButton{
                    id:backward
                    icon.source: !style.icon_pack_reset ? "image://icons/media-playback-back": ""
                    display:Button.IconOnly
                    //Layout.preferredWidth:window.state !== 0 ?window.height*0.10:window.height*0.15

                    //Layout.preferredHeight: width
                    width:window.state !== 0 ?window.height*0.10:window.height*0.15
                    height:width
                    icon.width: width/2
                    icon.height: height/2
                    onClicked: {
                        item.previous();
                    }

                }
                RoundButton{

                    width:backward.width
                    height:width
                    property bool isPlaying: btDevice.status === "playing"
                    icon.source: !style.icon_pack_reset ? "image://icons/media-playback-"
                                                          +(isPlaying ?"pause":"start") : ""
                    display:Button.IconOnly
                    icon.width: width/2
                    icon.height: height/2
                    onClicked: {
                        if(isPlaying){
                            item.pause()
                        }else{
                            item.play()
                        }
                    }
                }
                RoundButton{
                    width:backward.width
                    height:width
                    icon.source: !style.icon_pack_reset ? "image://icons/media-playback-next": ""
                    display:Button.IconOnly
                    icon.width: width/2
                    icon.height: height/2
                    onClicked: {
                        item.next()
                    }
                }
            }
        }


    }
}
