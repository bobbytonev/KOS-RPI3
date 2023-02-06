import QtQuick 2.0
import QtQuick.Controls 2.15
import Qt.labs.folderlistmodel 2.15
import QtQml.Models 2.15
import AppStarter 1.0
Item {
    id:item
    property string startingFolder

    property int highlightedSize: 0
    property bool foldersOnly: false
    property bool isSearching:false


    property alias col: col
    property alias copyMove: copyMove
    property alias textInput: textInput



    onVisibleChanged: {
        if(!visible){
            textInput.visible = false
            copyMove.visible=false

        }
    }

    Loader{
        signal fileClicked(string filePath);
        id:appLoader
        anchors.fill: parent
        asynchronous: true
        source:"Applications.qml"
        active:!foldersOnly
    }


    FolderListModel{
        id:folderModel
        showDirsFirst: true
        folder:"file://"+startingFolder
        rootFolder: "file://"+startingFolder
        showFiles: !foldersOnly
        Component.onCompleted: {
            if(foldersOnly) item.parent.path = startingFolder
        }


    }
    CopyMoveDialog{
        id:copyMove
        copyFlag:false
        onCopy:(filePath)=> {
                   col.moveFiles(filePath,copyFlag)
               }
        onMove:(filePath)=>{
                   col.moveFiles(filePath,copyFlag)
               }
    }




    Connections{
        target:window.manager
        function onBackClicked(){
            if(copyMove.visible){ return;}
            if(textInput.visible) textInput.visible = false
            else if(menu.visible) menu.visible = false
            else if(folderModel.folder.toString() != folderModel.rootFolder.toString()){

                var folder2 = folderModel.folder
                folderModel.folder = folder2.toString().substring(0,folder2.toString().lastIndexOf("/"));


            }else{
                if(!foldersOnly)
                    window.stackView.pop();
                else
                    item.parent.pop();
            }
        }

    }
    Connections{
        target:window
        function onActiveChanged(active){
            if(active){
                textInput.y = (window.height- window.keyboardHeight) - (textInput.height+window.headerHeight)

            }else{
                textInput.y = parent.height/2-textInput.height/2
            }
        }
    }
    TextInputDialog{
        id:textInput
        width:parent.width/3
        height:200
        focus:true
        modal:true
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        property bool newFolder: true
        inputTitle:!newFolder ? qsTr("Raname"):qsTr("Enter folder")
        onAccepted: {
            if(textInput.text.length > 0){
                if(newFolder)
                    window.fileManager.createFolder(folderModel.folder.toString().replace("file://","")
                                                    + "/"+textInput.text);
                else
                    col.rename(textInput.text)
            }
        }




    }
    Column{
        id:col
        anchors.fill: parent
        function search(text){
            for(var i =0;i<test.items.count;i++){
                var name = folderModel.get(i,"fileName");
                if(!name.includes(text)){
                    test.items.get(i).inSearch = true
                }else{
                    test.items.get(i).inSearch = false
                }
            }
        }

        function rename(newName){
            var tempPath = folderModel.get(test.currentIndex,"filePath")
            var path = tempPath.toString().substring(0,tempPath.toString().lastIndexOf("/"));
            console.log(tempPath,path,newName);
            fileManager.rename(tempPath,path+"/"+newName);
        }


        function deselectAll(){
            for(var i =0;i<test.items.count;i++){
                if(test.items.get(i).inSelected){
                    test.items.get(i).inSelected = false
                }
            }
            highlightedSize = 0
        }
        function selectAll(){
            for(var i =0;i<test.items.count;i++){
                test.items.get(i).inSelected = true
            }
        }

        function deleteFiles(){
            var listItems=[]

            for(var i =0;i<test.items.count;i++){
                console.log(i);
                if(test.items.get(i).inSelected){
                    listItems.push(folderModel.get(i,"filePath"))
                }
            }
            fileManager.remove(listItems);
        }
        function moveFiles(destination,copy){
            var listItems=[]
            var path =""
            for(var i =0;i<test.items.count;i++){
                if(test.items.get(i).inSelected){
                    listItems.push(folderModel.get(i,"fileName"))
                    if(path.length === 0){

                        var tempPath = folderModel.get(i,"filePath")
                        path = tempPath.toString().substring(0,tempPath.toString().lastIndexOf("/"));
                    }

                }
            }
            if(copy)
                fileManager.copy(path,listItems,destination);
            else
                fileManager.move(path,listItems,destination);

        }

        Connections{
            target:stackView
            function onBusyChanged(){
                if(!foldersOnly && !topPanelLoader.active && !stackView.busy)
                    topPanelLoader.active=true
            }
        }

        Loader{
            id:topPanelLoader
            active:false
            asynchronous: true
            width:parent.width
            height:window.height*0.08
            source:"TopPanel.qml"

        }

        DelegateModel{
            id:test
            model:folderModel
            property int currentIndex: -1
            onCountChanged: {
                highlightedSize = 0;
            }

            groups: [
                DelegateModelGroup{name:"selected"},
                DelegateModelGroup{name:"search"}

            ]
            delegate:Button{
                property bool folder:folderModel.isFolder(index)
                icon.source: !style.icon_pack_reset ? "image://icons/"+(folder ? "folder":"file"): ""
                text:fileName
                width:view.width
                height:window.height*0.12
                visible:!DelegateModel.inSearch
                highlighted:DelegateModel.inSelected

                onClicked: {

                    if(highlightedSize !=0){
                        DelegateModel.inSelected = !DelegateModel.inSelected
                        highlightedSize+= highlighted ? 1:-1

                    }else if(folder){
                        folderModel.folder = fileUrl
                        if(foldersOnly) item.parent.path = filePath
                    }else{
                        appLoader.fileClicked(filePath)
                    }



                }onPressAndHold: {

                    if(foldersOnly) return;

                    if(highlightedSize===0) test.currentIndex = index

                    DelegateModel.inSelected = !DelegateModel.inSelected
                    highlightedSize+= highlighted ? 1:-1
                }
            }
        }

        MenuSeparator{
            visible:!foldersOnly
            width:parent.width
        }
        Item{id:seperator;width:1;height:window.height*0.06}

        ListView{


            width:parent.width
            height:item.height-(seperator.y+seperator .height)
            property string fileType
            property string iconName
            id:view

            model:test
            spacing:10


        }

    }


}
