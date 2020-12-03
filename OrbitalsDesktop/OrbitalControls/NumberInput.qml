import QtQuick 2.15
import QtQuick.Controls 2.14

import Theme 1.0

TextInput {
    property int suggestedMinimumWidth: 20
    selectByMouse: true
    rightPadding: 10

    Rectangle {
        z: -1
        anchors.fill: parent
        anchors.margins: -5
        anchors.bottomMargin: -1
        anchors.rightMargin: 0
        color: parent.enabled ? "white" : Qt.lighter(Theme.bgColor, 1.3)
        opacity: 0.9
        border.color: "grey"
        radius: 5
    }
}
