import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.15

Item {
    property var naming: [qsTr("Icon size"),qsTr("Image vertical alignment")
        ,qsTr("Image horizontal alignment"),qsTr("Image fill mode")]
    height:parent.height



    property var pageNaming: ["IconSize","ImageVerticalAlignment","ImageHorizontalAlignment","ImageFillMode"] //can be improved

    ScrollView{
        width:window.width
        height:parent.height
        Column{
            width:window.width
            SettingsButton{
                width:window.width
                height:window.height*0.12
                title:naming[0];
                buttonLogic: [0.19,0.25,0.30];
                buttonNames: [qsTr("Small"),qsTr("Medium"),qsTr("Large")]
                hightlightValue:settings.appsIconSize
                onClicked: (index) =>{
                               settings.appsIconSize=buttonLogic[index]
                               hightlightValue=settings.appsIconSize
                               hightlightValue=hightlightValue
                           }
            }


            Switch{
                text:qsTr("Show icon text")
                checked:settings.iconText
                width: parent.width
                height: window.height*0.12
                onCheckedChanged: {
                    settings.iconText=checked
                }

            }
            MenuSeparator{
                width:parent.width
            }
            SettingsButton{
                width:window.width
                height:window.height*0.12
                title:naming[1];
                buttonNames: [qsTr("Top"),qsTr("Bottom"),qsTr("Center")]
                buttonLogic: [Image.AlignTop,Image.AlignBottom,Image.AlignVCenter];
                hightlightValue:settings.backgroundVerticalAlignment
                onClicked: (index) =>{
                               settings.backgroundVerticalAlignment=buttonLogic[index]
                               hightlightValue=settings.backgroundVerticalAlignment
                               hightlightValue=hightlightValue
                           }
            }
            SettingsButton{
                width:window.width
                height:window.height*0.12
                title:naming[2];

                buttonNames: [qsTr("Left"),qsTr("Right"),qsTr("Center")]
                buttonLogic: [Image.AlignLeft,Image.AlignRight,Image.AlignHCenter];
                hightlightValue:settings.backgroundHorizontalAlignment
                onClicked: (index) =>{
                               settings.backgroundHorizontalAlignment=buttonLogic[index]
                               hightlightValue=settings.backgroundHorizontalAlignment
                               hightlightValue=hightlightValue
                           }
            }
            RowLayout {
                width:parent.width
                height:window.height*0.12

                id:rowLayout
                spacing:10

                Label{
                    Layout.fillWidth: true
                    id:title
                    text:naming[3]
                    Layout.fillHeight: true

                }


                ComboBox{
                    model: [qsTr("Stretch"),qsTr("Aspect fit"),qsTr("Aspect crop")
                        ,qsTr("Tile"),qsTr("Pad")]
                    property var buttonLogic: [Image.Stretch,Image.PreserveAspectFit , Image.PreserveAspectCrop ,Image.Tile,Image.Pad];
                    Layout.preferredWidth:parent.width/4
                    currentIndex: buttonLogic.indexOf(settings.backgroundFillMode);


                    onCurrentIndexChanged: {
                        settings.backgroundFillMode=buttonLogic[currentIndex]

                    }

                }
                Item{
                    Layout.preferredWidth: 16
                }
            }



            MenuSeparator{
                width: parent.width
            }
            Switch{
                id:blurBackground
                text:qsTr("Blur background")
                checked:settings.blur
                width: parent.width
                height:window.height*0.12
                onCheckedChanged: {
                    settings.blur=checked
                }

            }
            Switch{
                text:qsTr("Allways")
                checked:settings.alwaysBlur
                width: parent.width
                enabled: blurBackground.checked
                height:window.height*0.12
                onCheckedChanged: {
                    settings.alwaysBlur=checked
                }

            }


        }

    }
}
