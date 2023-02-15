import QtQuick 2.0
import QtQuick.Controls 2.2


Dialog{
    id:clockDialog
    modal:true
    visible:dialogLoader.openDialog
    x:parent.width/2-width/2
    y:parent.height/2-height/2
    property bool apFormat: dialogLoader.apFormat
    onClosed: {
         dialogLoader.openDialog = false
    }

    property var currentTime:[0,0]
    function setCurrentTime(){
        currentTime = Qt.formatDateTime(new Date(),"hh:mm"+(apFormat ? " ap" : "")).split(":");
        if(apFormat){
            currentTime[1]=currentTime[1].split(" ")[0]
            currentTime[0]-=1;
        }

        currentTime = currentTime;

    }
    onOpened: {
        Qt.callLater(setCurrentTime)
    }

    header:Item{}
    footer:Item{}
    function convertTo24(hours,modifier){


        if (hours === 12) {
            hours = 0;
        }

        if (modifier === 'PM') {
            //hours = parseInt(hours, 10) + 12;
            hours+=12;
        }


    }

    function formatText(count, modelData) {
        var data = count === 12 ? modelData+1  : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }


    Component {
        id: delegateComponent

        Label {
            text: formatText(Tumbler.tumbler.count, modelData)
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

        }
    }





    contentItem:Column{
        anchors.centerIn: parent
        Row {
            id: row

            Item{
                width:amPmTumbler.width/2
                height:amPmTumbler.height
                visible:!apFormat
            }
            Tumbler {
                id: hoursTumbler
                model:apFormat ? 12:24
                currentIndex:currentTime[0]
                delegate: delegateComponent

            }

            Tumbler {
                id: minutesTumbler
                model: 60
                delegate: delegateComponent
                currentIndex:Number(currentTime[1])

            }

            Tumbler {
                id: amPmTumbler
                visible:apFormat
                currentIndex:0
                model:["AM", "PM"]

            }
        }
        Row{

            Button{
                text:qsTr("Okay")

                onClicked:{
                    var h,m,modifier;
                    modifier=amPmTumbler.currentItem.text
                    h=hoursTumbler.currentItem.text
                    m=minutesTumbler.currentItem.text
                    if(apFormat){
                        convertTo24(h,modifier);

                    }

                    dialogLoader.timePicked(h+":"+m+":00")
                    close();
                }

            }
            Button{

                text:qsTr("Cancel")

                onClicked:{
                    close();
                }

            }


        }

    }




}
