import QtQuick 2.12
import QtQuick.Controls 2.12
import Languages 1.0


ListView{
    id:view
    //anchors.fill: parent
    maximumFlickVelocity:5000
    model:LanguageModel{id:languages;}
    delegate:Button{
        height:window.height*0.12
        width:view.width
        text:name
        highlighted: lang.language===prefix
        onClicked:{
            if(!highlighted){

                lang.language=prefix
                window.pageView.pop();


            }
        }

    }
}

