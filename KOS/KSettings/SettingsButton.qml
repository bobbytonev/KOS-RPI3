import QtQuick 2.0
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
RowLayout {
    id:rowLayout
    spacing:10
    property var buttonNames:[]
    property var buttonLogic:[]
    property alias title: title.text
    property var hightlightValue

    signal clicked(var index);
    Label{
        Layout.fillWidth: true
        id:title
        Layout.fillHeight: true

    }


    Repeater{
      model:buttonNames.length
      Button{

          display:Button.TextOnly
          text:buttonNames[index]

          highlighted: hightlightValue == buttonLogic[index]
          onClicked: {
              rowLayout.clicked(index);
          }
      }
    }
    Item{
       Layout.preferredWidth: 16
    }
}
