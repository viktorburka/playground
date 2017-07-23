import QtQuick 2.0
import CustomGeometry 1.0
Item {
    width: 300
    height: 200

    SineItem {
        id: line
        anchors.fill: parent
        anchors.margins: 20
        property real t
        SequentialAnimation on degree {
            NumberAnimation { to: 360; duration: 2000; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 0; duration: 2000; easing.type: Easing.InOutQuad }
            loops: Animation.Infinite
        }
    }
}
