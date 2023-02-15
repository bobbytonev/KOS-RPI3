import QtQuick 2.0
import QtQuick.Controls 2.12
import MimeTypes 1.0
Item {
    id:item
    function setMimeType(text){
        var list =database.getMimetype(text)
        if(list.length !== 0 ){mimetypesLoader.mimeType(list[0],list[1])}
    }

    TextInputDialog{
        //z:200
        property bool accept: false
        id:textInput
        width:parent.width/3
        height:200
        focus:true
        modal:true
        visible:mimetypesLoader.requestOpen&&item.visible
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        inputTitle:qsTr("Enter extension")

        onAccepted: {
            // Qt.callLater(item.setMimeType,textInput.text)
            //database.requestMimetype(textInput.text)
            accept=true

        }
        onRejected: {
            accept=false
        }
        onClosed: {
            mimetypesLoader.requestOpen=false

            if(accept) Qt.callLater(database.requestMimetype,textInput.text)

        }


    }


    MimeTypes{
        id:database
        onMimetypeChanged:(mimeType)=>{
                              mimetypesLoader.mimeType(mimeType[0],mimeType[1])
                          }
    }

    Connections{
        target:window
        function onActiveChanged(active){
            if(active){
                //textInput.y = (window.height - window.keyboardHeight) - (textInput.height+window.headerHeight)
                textInput.y = (item.height-window.keyboardHeight) - (textInput.height)
            }else{
                textInput.y = parent.height/2-textInput.height/2
            }
        }
    }


    Connections{
        target:window
        function onBackButtonClicked(){
            if(pop.visible){
                window.block = true

            }

        }
    }

}
