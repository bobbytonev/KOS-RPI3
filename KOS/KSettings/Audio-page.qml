import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
//import Qt.labs.settings 1.1
import VolumeControl 1.0
Item {
    id:item
    Column{
        width:parent.width

        RowLayout{

            width:parent.width

            Item{
                Layout.preferredWidth: masterVolume.height
            }
            RoundButton{
                id:masterVolume
                display:Button.IconOnly
                Layout.preferredHeight: window.height*0.10
                Layout.preferredWidth: masterVolume.height

                icon.source:{
                    if(!style.icon_pack_reset){

                        if(volumeControl.volume === 0)
                            return "image://icons/audio-volume-zero-panel"
                        else if(volumeControl.volume < 25)
                            return "image://icons/audio-volume-low-panel"
                        else if(volumeControl.volume < 75)
                            return "image://icons/audio-volume-medium-panel"
                        else if(volumeControl.volume > 75)
                            return "image://icons/audio-volume-high-panel"

                    }else{

                        return "";
                    }

                    //!style.icon_pack_reset ? "image://icons/master-volume": ""
                }


                // Layout.fillHeight:true

                onClicked:{
                    volumeControl.volume=0
                }
            }
            Slider{
                id:volumeSlider
                Layout.fillWidth :true
                Layout.preferredHeight:window.height*0.12
                value: volumeControl.volume
                stepSize:1

                from:0//volumeControl.min
                to:100//volumeControl.max
                onValueChanged: {
                    //volumeControl.volume=value;
                    volumeChangeTimer.restart()
                }

            }
            Label{

                Layout.fillHeight:true
                //Layout.preferredWidth: masterVolume.height
                text:volumeSlider.value//volumeControl.volume
            }

            Item{
                Layout.preferredWidth: masterVolume.height*2
            }


        }

        MenuSeparator{
            id:separator
            width:parent.width
        }

    }
    Timer{
        id:volumeChangeTimer
        interval:150
        onTriggered: {
            volumeControl.volume = volumeSlider.value
        }
    }

    VolumeControl{
        id:volumeControl
    }
}
