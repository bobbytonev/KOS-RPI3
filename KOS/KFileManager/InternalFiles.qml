import QtQuick 2.0
import QtQuick.Controls 2.15
import InternalFilesModel 1.0
Item{
    property string fileType
    property string iconName
    Loader{
        id:appLoader
        signal fileClicked(string filePath);
        anchors.fill: parent
        asynchronous: true
        active:true
        source:"Applications.qml"
    }

    ListView{
        anchors.fill:parent
        id:view
        model:InternalFilesModel{type:fileType}

        Connections{
            target:window.manager
            function onBackClicked(){
                window.stackView.pop();

            }

        }

        delegate:Button{

            icon.source: !style.icon_pack_reset ? iconName:""
            text:fileName
            width:view.width
            height:window.height*0.12
            onClicked: {
                appLoader.fileClicked(fileUrl)
            }

        }
    }
}
