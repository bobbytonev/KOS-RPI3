import QtQuick 2.0
import QtQuick.Controls 2.2


Dialog{
    id:dateDialog
    visible:dialogLoader.openDialog
    modal:true
    x:parent.width/2-width/2
    y:parent.height/2-height/2
    width:400
    onClosed: {
        dialogLoader.openDialog = false
    }


    property var years:[]
    property var currentDate:[]
    property var months:[31,28,31,30,31,30,31,31,30,31,30,31]

    header:Item{}
    // footer:Item{}
    onOpened: {
        if(years.length === 0){
            Qt.callLater(fillUpYears)

        }
        Qt.callLater(setCurrentDate);
    }

    function setCurrentDate(){
        currentDate = Qt.formatDateTime(new Date(),"M d yyyy").split(" ");
        currentDate =currentDate;
    }

    function fillUpYears(){
        for(var i=1970;i<2037;i++){
            years.push(i);
        }
        years=years;
    }

    function checkLeapYear(year) {


        if ((0 == year % 4) && (0 != year % 100) || (0 == year % 400)) {
            return true;
        } else {
            return false;
        }
    }

    function formatText(count, modelData) {
        var data = count <= 40 ? modelData + 1 : modelData;
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


    contentItem:Item{

        Row {
            id: row
            // anchors.centerIn: parent
            anchors.fill: parent
            Tumbler {
                id: month
                model: 12
                width:parent.width/3
                delegate:delegateComponent
                currentIndex:currentDate[0]-1

            }

            Tumbler {
                id: day
                width:parent.width/3
                model:month.currentIndex === 1&&checkLeapYear(year.currentIndex) ? 29: months[month.currentIndex]
                delegate:delegateComponent
                currentIndex:currentDate[1]-1

            }

            Tumbler {
                id: year
                model:years
                width:parent.width/3
                currentIndex:currentDate[2]-1970

            }
        }


    }
    footer:Row{
        Item{width:20;height:1}
        Button{
            text:qsTr("Okay")
            display:Button.TextOnly
            width:(parent.width/2)-20
            height: 48
            onClicked:{
                var y = year.currentIndex+1970;
                var m = month.currentItem.text
                var d = day.currentItem.text
                // hwclock.setTimeDate(d+"-"+m+"-"+y,false);
                dialogLoader.datePicked(d+"-"+m+"-"+y);
                close();


            }

        }
        Button{
            height:48
            text:qsTr("Cancel")
            display:Button.TextOnly

            width:(parent.width/2)-20
            onClicked:{
                close();
            }
            Item{width:20;height:1}


        }

    }

}





