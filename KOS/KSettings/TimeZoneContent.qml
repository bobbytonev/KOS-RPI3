import QtQuick 2.12
import TimeZonesModel 1.0
import QtQuick.Controls 2.15
Item {
    id:item
    anchors.fill:parent

    property var searchModel:[]
    property bool isFiltered: false



    function filter(text){
        //var text = field.text
        searchModel=[]
        var list = timeZones.getList();
        for(var i = 0;i < list.length;i++){
             // console.log(list[i],text);
            if(list[i].includes(text)){
                searchModel.push(list[i])
            }
        }
        isFiltered = true
    }





    TimeZonesModel{
        id:timeZones
    }



    Column{
        anchors.fill:parent

        Row{
            id:row
            width:parent.width
            Button{
                id:search
                icon.source: !style.icon_pack_reset ? "image://icons/filesystem-search": ""
                display:Button.IconOnly
                height:window.height*0.09
                width:height
                onClicked:{

                    field.visible=!field.visible



                }
            }
            TextField{
                id:field
                visible:false
                height:row.height
                Keys.onReturnPressed:Qt.callLater(filter,field.text);
                onVisibleChanged: {
                    if(!visible){
                        text=""
                        isFiltered = false
                    }else{
                        field.focus=true

                    }
                }


            }


        }

        Item{height:window.height*0.12;width:1}

        ListView{
            id:view
            width:parent.width
            height:parent.height-(row.height)
            model:isFiltered ? searchModel:timeZones

            delegate:Button{
                text:isFiltered ? searchModel[index]:timeZone
                width:view.width
                height:window.height*0.12

                onClicked:{

                    //hwclock.setTimeZone(text);
                    timeZones.setTimeZone(text);
                    window.pageView.pop();


                }
            }


        }
    }
}
