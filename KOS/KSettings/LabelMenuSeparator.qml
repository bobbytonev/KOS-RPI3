import QtQuick 2.15
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15
RowLayout {
    id:row
    width: parent.width
    spacing:20
    property alias text: label.text
    MenuSeparator{
        Layout.fillWidth: true
    }

    Label{
        id:label

        leftPadding: 0
        padding: 0
        horizontalAlignment: Text.AlignVCenter
        verticalAlignment: Text.AlignVCenter


    }
    MenuSeparator{
        Layout.fillWidth: true
    }



}

