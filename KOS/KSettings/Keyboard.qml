import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.2

InputPanel {
    id: inputPanel
    z: 99
    x: 0
    y: window.height
    width: window.width
    onActiveChanged:{
        if(window.keyboardHeight===0&&active) window.keyboardHeight= height+30
        window.activeChanged(inputPanel.active);

    }

    Connections{
        target:manager
        function onStateChanged(status){
                           if(status === 0 && inputPanel.active){
                               inputPanel.active = false;
                           }
                        }

    }

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
