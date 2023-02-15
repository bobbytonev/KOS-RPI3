import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.15
Item{

    id:popup
    property bool iconPack:false

    onVisibleChanged: {



        if(!visible){
            iconPack=false
        }
    }


    FolderListModel {
        id: styleModel
        showDirsFirst: true
        folder:"file:///usr/share"+(iconPack ?"/icons/" :"/themes/")

    }
    ListView{
        id:view
        anchors.fill:parent
        model:styleModel
        delegate:Button{

            highlighted:iconPack&&style.iconPack()===fileName||style.styleName()===fileName
            text:fileName
            width:view.width
            height:window.height*0.12
            onClicked:{

                if(!highlighted){

                    style.changeStyle(fileName,iconPack);

                }

                window.pageView.pop();

            }
        }
    }
}
