import QtQuick 2.0
import BluetoothDeviceModel 1.0
import QtQuick.Controls 2.15
ListView {
    id:view
    //anchors.fill: parent
    model:BluetoothDeviceModel{}
    spacing:15


    add:Transition{
        NumberAnimation{duration:200;property:"scale";to:1;from:0}
    }
    remove:Transition{
        NumberAnimation{duration:200;property:"width";to:0;from:1}
    }
    move:Transition{
        NumberAnimation{duration:200;property:"y";}
    }

    delegate:BtDevice{

        width:view.width
    }
}
