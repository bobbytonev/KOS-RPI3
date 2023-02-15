import QtQuick 2.8
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15
Item {

    property var buttonNames : [qsTr("Styles"),qsTr("Style-config"),qsTr("Icon Pack")]
    property var propertyIndex

    ListView{
        anchors.fill: parent
        id:view
        header:Column{
            width: parent.width
            Repeater{
                model:buttonNames.length
                Button{
                    id:pair
                    width: parent.width
                    text:qsTr(buttonNames[index]);
                    height:window.height*0.12


                    onClicked:{
                        if(index===0){
                            window.pageView.push("Style-page.qml");
                        }else if(index===1)

                            window.pageView.push("StyleConfig.qml");
                        else{
                            window.pageView.push("Style-page.qml",{iconPack:true});
                        }


                    }

                }
            }

        }


    }

}


