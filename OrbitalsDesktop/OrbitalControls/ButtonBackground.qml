import QtQuick 2.15

Rectangle {
    implicitWidth: 150
    implicitHeight: 40
    opacity: enabled ? 1 : 0.3
    color: parent.down ? "#6b7080" : "#848895"
    border.color: "#222840"
    border.width: 1
    radius: 5
}