import QtQuick 2.0
import AllApplications 1.0
import QtQuick.Controls 2.12


Item{
 id:information
  property var confLocation
Component.onCompleted: {
    if(!loader.active)loader.active=true
}
Loader{
    anchors.fill: parent
    id:loader
    active:false
    source:"AppInfoContent.qml"

}

}

