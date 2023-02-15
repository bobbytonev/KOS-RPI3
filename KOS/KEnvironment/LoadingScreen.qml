import QtQuick 2.0
import QtQuick.Controls 2.15
Popup {
    visible:true
    Image{
        anchors.centerIn: parent
        source: !style.icon_pack_reset ? "image://icons/"+appLoading.icon : ""

    }
}
