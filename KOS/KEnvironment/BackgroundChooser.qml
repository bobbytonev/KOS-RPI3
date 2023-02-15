import QtQuick 2.0
import Qt.labs.folderlistmodel 2.15
import QtQuick.Controls 2.12
import ImageFiles 1.0
Item {

    /*
    Image{
       // anchors.fill: parent
        asynchronous: true
        sourceSize.width: parent.width
        sourceSize.height: parent.height
        source:settings.source
        opacity: 1



    }
    */
    property string bgSource
    SequentialAnimation{
        id:imageChangeAnimation
        NumberAnimation{
            id:animation
            target:fastBlur
            property: "opacity"
            from:1
            to:0
            duration:200
            easing.type: Easing.InOutQuad
        }
        ScriptAction{
            script:settings.source = bgSource
        }
        NumberAnimation{
            target:animation.target
            property: "opacity"
            from:0
            to:1
            duration:300
            easing.type: Easing.InOutQuad

        }
    }


//    FolderListModel {
  //      id: imageModel
    //    showDirsFirst: false
      //  nameFilters: ["*.png","*.jpg","*.jpeg"]
        //folder:"file://+"+_homeDir+"/0/images"

    //}
    ImageFiles{
        id:imageModel
    }
    Label{
        anchors.centerIn: parent
        font.pixelSize: 32
        text:qsTr("No images found")
        visible:imageView.count < 1
    }

    ListView{
        id:imageView
        z:2
        // y:20
        width: parent.width
        height:parent.height/1.5
        y:parent.height/2-height/2
        model:imageModel
        delegate:Pane{
            width:image.width+20
            height:image.height+20


            MouseArea{
                anchors.fill: parent
                onClicked: {
                    //  settings.source = image.source
                    bgSource = image.source
                    imageChangeAnimation.start()
                }
            }

            Image{
                id:image
                width:window.width/8
                height:window.height/8
                sourceSize.width: width
                sourceSize.height: height
                anchors.centerIn: parent
                asynchronous: true
                source:fileUrl


            }
        }
    }

}
