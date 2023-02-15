import QtQuick 2.0
import QtQuick.Controls 2.2
//import QtQuick.VirtualKeyboard 2.2
import FontsModel 1.0
Item{
    BusyIndicator{
        anchors.centerIn: parent
        running:styleLoader.status == Loader.Loading
    }
    Connections{
        target:pageView
        function onBusyChanged(){
            if(!pageView.busy && !styleLoader.active)
                styleLoader.active=true;
        }
    }
    Loader{
        id:styleLoader
        anchors.fill: parent
        asynchronous: true
        source:"file:///usr/share/themes/"+style.styleName()+"/style.qml"
        visible:status == Loader.Ready
        active:false

    }
}
/*
Item{
    id:item
    InputPanel {
        id: inputPanel
        z: 1
        x: 0
        y: window.height
        width: window.width


        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }




    Component.onCompleted: {

        var currentGroup =""


        for(var property in themeData){
            var value =themeData[property];


            if(currentGroup!==value[0]&&value[0]!==undefined){
                var componente = Qt.createComponent("LabelMenuSeparator.qml")


                componente.createObject(column,{text:value[0]});
                currentGroup=value[0];
            }


            if(value[0]==="Color"){
                var button =buttonComponent.createObject(column,{"prop":property,"data":value,"width":column.width,"height":window.height*0.12});

            }else if(value[0]==="Switch"){

                var sw =switchComponent.createObject(column,{"text":property,"prop":property,"data":value,"width":column.width,"height":window.height*0.12});

            }else if(value[0]==="Buttons"){

                if(property.indexOf("_array")>-1){

                    var key =property.replace("_array","");
                    var val =themeData[key];

                    var b =bComponent.createObject(column,{"text":key+":"+val[1],"prop":key,"data":value,"width":column.width,"height":window.height*0.12});

                }
            }else if(value[0]==="Sliders"){
                if(property.indexOf("_array")>-1){

                    var svKey =property.replace("_array","");
                    var sv =themeData[svKey];


                    var sl =sComponent.createObject(column,{"dataValue":sv[1],"prop":svKey,"propArray":property,"data":value,"width":column.width,"height":window.height*0.12});

                }
            }else if(value[0]==="Font"){
                var fonts =["Font",Qt.fontFamilies()];
                var fb =bComponent.createObject(column,{"isFont":true,"text":value[1],"prop":property,"data":fonts,"width":column.width,"height":window.height*0.12});
            }



        }


    }
    ColorChooserDialog {
        id: colorDialog

        property var data
        property var button
        property var prop
        //width:parent.width
        //height: parent.height
        //x:parent.width/2-width


        Connections{
            target:window
            function onBackButtonClicked(){
                if(colorDialog.visible){
                    window.block =true;
                    colorDialog.close();

                }

            }
        }

        onAccepted: {

            style.overrideProperty(prop,data[0],colorDialog.colorValue);

            button.text=colorDialog.colorValue
        }
        onRejected: {
            colorDialog.close()
        }


    }

    Popup{

        id:popup
        visible: false
        //width: parent.width/2
        //height: parent.height/2
      //  x:parent.width/2 - width/2
        //y:parent.height/2-height/2


        //closePolicy: Popup.CloseOnPressOutside
        property var prop
        modal:true
        property var values:[]
        property var group

        property var choose

        property var button

        property bool isFont:false


        Connections{
            target:window
            function onBackButtonClicked(){
                if(popup.visible){
                    window.block =true;
                    popup.close();


                }

            }
        }

        ListView{
            anchors.fill: parent
            clip:true
            id:view
            header:Column{
                id:col
                width: parent.width

                Repeater{
                    model:popup.values.length
                    delegate: Button{
                        text:popup.values[index]
                        highlighted:popup.button.text===popup.prop+":"+text;
                        width:parent.width
                        font.family: popup.isFont ? text : font.family
                        onClicked: {
                            style.overrideProperty(popup.prop,popup.group,popup.values[index]);

                            popup.button.text=popup.prop+":"+popup.values[index];
                            popup.close();


                        }
                    }

                }

            }
        }

    }

    Component{
        id:switchComponent
        Switch{

            id:sw
            property var prop


            property var data
            checked: data[1]==="true" ?  true:false
            onCheckedChanged: {

                style.overrideProperty(prop,data[0],checked);
            }

        }

    }



    Component{
        id:bComponent

        Button{

            id:button

            property var data


            property var prop
            property bool isFont:false
            onClicked: {

                if(!isFont)

                    popup.values=data[1].split("!");
                else{
                    popup.isFont = isFont
                    popup.values =data[1];
                }


                popup.prop=prop
                popup.group=data[0];
                popup.button=button;
                popup.open();



            }





        }


    }
    Component{
        id:rect
        Rectangle{
            width: 32
            height:width


            x:parent.contentItem.leftPadding >=width/2&& parent.contentItem.leftPadding<=parent.width/2? parent.width-width*2 : 0

            y:parent.height/2-height/2
            border.color: color.hslLightness > 0.5 ?"black":"white"
            border.width:1


        }

    }

    Component{
        id:sComponent

        Slider{
            property var prop
            property var data
            property  var minMax: data[1].split("!");

            property var dataValue

            from:minMax[0];
            to:minMax[1];
            value:dataValue

            onValueChanged: {
                style.overrideProperty(prop,data[0],value);
            }

        }

    }

    Component{
        id:buttonComponent


        Button{

            property var prop
            property var data

            id:button


            text:button.data[1];

            property  var rectangle

            onClicked: {

                colorDialog.prop=button.prop;
                colorDialog.data=button.data;
                colorDialog.button=button;
                colorDialog.open();

            }
            onTextChanged: {

                if(rectangle===undefined) return;

                rectangle.color=text


            }

            Component.onCompleted: {
                rectangle=rect.createObject(button,{"color":data[1]});
            }


        }




    }


    ScrollView{
        anchors.fill: parent
        clip:true
        ScrollBar.horizontal.policy:ScrollBar.AlwaysOff
        ScrollBar.vertical.policy:ScrollBar.AlwaysOff
        Column{
            id:column
            width:parent.width




        }
    }





}
*/
