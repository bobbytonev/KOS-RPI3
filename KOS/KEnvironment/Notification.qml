import QtQuick 2.0
import QtQuick.Controls 2.15
//0 - Low - noPoup , can be removed
//1 - Normal - popup , can be removed
//2 - Medium - noPopup , cant be removed
//3 - High - popup ,cant be removed
//4 - Ultra - stickyPopUp, cant be removed
Pane {
    id:pane
    width:parent.width
    height:customNotification.active ? customNotification.height+20 : column.height+20






    background:Rectangle{

        color:"#000000"
        radius:20
    }


    property real maximumX: window.width - pane.width
    opacity: x < 0 ? (maximumX+x)/maximumX : (maximumX-x)/maximumX



    MouseArea{
        id:mouse
        anchors.fill: parent
        drag.target:priorityId < 2 ? pane :null

        drag.axis: Drag.XAxis
            onPressed: {
                timerRunning = false
            }
            onClicked: {
                notifyList.sendSignal(aName,nId,"Clicked")
            }

        onReleased: {

            if(pane.opacity>0.6){
                popAnimation.from = pane.x
                popAnimation.to = 0

            }else{
                popAnimation.from = pane.x
                popAnimation.to = pane.x < 0 ? -maximumX : maximumX

            }

            timerRunning = true
            popAnimation.start()
        }


    }

    NumberAnimation{
        id:popAnimation
        target:pane
        property: "x"
        from:pane.x
        to:0
        duration: 200

    }


    // QString appName,imagePath,title,text="",qmlPath="";
    //int notifyId;
    //int priority=1;
    //bool imageProvider;
    //QStringList buttons={};

    //signal notificationChanged()
    property bool timerRunning:true
    property string aName
    property string iPath
    property string customQml
    property int nId
    property int priorityId
    property alias appImage: appImage.source
    property alias nTitle: title.text
    property alias notifyImage: notifyImage.source
    property alias bodyLabel:bodyLabel.text
    property var menus:[]
    property  int menusSize


    onMenusSizeChanged: {
        menus=menus

    }

    Loader{
        width:parent.width

        id:customNotification
        source:customQml
        active:customQml.length > 0
        clip:true
    }


    Column{
        id:column
        width:parent.width-20
        anchors.centerIn: parent
        spacing:5
        visible:!customNotification.active

        Row{
            id:header
            width:parent.width

            //Item{}


            Image{
                id:appImage
                width:32
                height:32
            }
            Label{
                id:title



            }

        }
        MenuSeparator{
            width:parent.width
        }

        Row{
            visible:true
            width:parent.width
            spacing: 10
            height:bodyLabel.height
            Item{id:spacer;width:32}
            Label{
                id:bodyLabel
                width:parent.width-(spacer.width*2 + spacing*2)
                wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                font.pixelSize: title.font.pixelSize-2


            }
            Image{
                id:notifyImage
                width:32
                height:width


            }

        }
        Row{
            spacing:5
            width: parent.width
            Repeater{
                model:menus.length > 4 ? 4 : menus.length
                Button{
                    text:menus[index]
                    display:Button.TextOnly
                    onClicked: {
                        notifyList.sendButtonSignal(index,aName,nId,"MClicked");
                    }
                }
            }
        }


    }





}
