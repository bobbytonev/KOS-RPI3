import QtQuick 2.0
import QtQuick.Controls 2.2
import HwClock 1.0

Item {
    id:item

    HardwareClock{
        id:hwclock
        active:true

    }
    Loader{
        anchors.fill: parent
        id:dialogLoader
        property bool openDialog: false
        property bool apFormat: false
        active:false
        asynchronous: true
        //source:"DateDialog.qml"
        signal datePicked(string date);
        signal timePicked(string date);

        onDatePicked:(date)=>{
                         hwclock.setTimeDate(date,false)
                     }
        onTimePicked: (time)=>{
                          hwclock.setTimeDate(time,true);
                      }
    }
    /*
    Loader{
        anchors.fill: parent
        id:dialogLoader
        property bool apFormat: false
        property bool openDialog: false

        active:false
        asynchronous: true
        source:"ClockDialog.qml"
        signal timePicked(string date);
        onTimePicked: (time)=>{
                          hwclock.setTimeDate(time,true);
                      }
    }
    */

    /*
    DateDialog{
        id:dateDialog
        onDatePicked:(date)=>{
                         console.log(date);
                         hwclock.setTimeDate(date,false)
                     }
    }

    ClockDialog{
        id:clockDialog
        onTimePicked: (time)=>{
                          console.log(time);
                          hwclock.setTimeDate(time,true);
                      }
    }
    */

    ListView{
        id:view
        anchors.fill: parent
        model:1
        delegate: Column{
            Switch{
                id:dateTime
                text:qsTr("Automatic date & time")
                height: window.height*0.12
                width: view.width
                checked: hwclock.ntp
                onClicked: {
                    hwclock.ntp = checked
                }
            }
            Button{
                id:systemDate

                width: view.width
                enabled:!dateTime.checked
                height: window.height*0.12
                //text:Qt.formatDateTime(new Date(),"MMM ddd, yyyy");
                Timer{
                    interval: 500; running:true ; repeat: true
                    onTriggered: {

                        //var s =Qt.formatDateTime(new Date(),"MMM dd, yyyy");
                        systemDate.text =Qt.formatDateTime(new Date(),"MMM ddd, yyyy");
                    }
                }
                onClicked:{
                    if(!dialogLoader.active)dialogLoader.active = true

                    dialogLoader.source = "DateDialog.qml"
                    dialogLoader.openDialog = true
                    //dateDialog.open()
                }
            }
            Button{
                id:systemTime

                width: view.width
                enabled:!dateTime.checked
                height:window.height/8
                //text:Qt.formatDateTime(new Date(),"hh:mm"+(hwclock.apFormat ? " ap" : ""));
                Timer{
                    interval: 500; running:true ; repeat: true
                    onTriggered: {
                        systemTime.text =Qt.formatDateTime(new Date(),"hh:mm"+
                                                           (hwclock.apFormat ? " ap" : ""));



                    }

                }
                onClicked:{
                    if(!dialogLoader.active) dialogLoader.active = true

                    dialogLoader.source = "ClockDialog.qml"
                    dialogLoader.apFormat = hwclock.apFormat
                    dialogLoader.openDialog=true;
                    //clockDialog.open()
                }
            }

            MenuSeparator{
                width: view.width
            }

            Button{
                id:systemTimeZone
                width: view.width

                height: window.height*0.12


                Timer{
                    interval: 500; running:true ; repeat: true

                    onTriggered: {

                        var a = new Date().getTimezoneOffset();
                        var res = -Math.round(a/60)+':'+-(a%60);
                        res = res < 0 ?res : '+'+res;

                        systemTimeZone.text ="UTC"+res;
                    }
                    Component.onCompleted: {
                        //var a = new Date().getTimezoneOffset();
                        //var res = -Math.round(a/60)+':'+-(a%60);
                        //res = res < 0 ?res : '+'+res;

                        //systemTimeZone.text ="UTC"+res;
                    }
                }
                onClicked:{

                    window.pageView.push("TimeZone-page.qml");
                }
            }
            MenuSeparator{
                width: view.width
            }
            Switch{
                id:amPm
                text:qsTr("Use 12-hours format")
                height: window.height*0.12
                width: view.width
                checked:hwclock.apFormat;
                onCheckedChanged: {
                    hwclock.apFormat=checked
                }

            }

        }
    }

}
