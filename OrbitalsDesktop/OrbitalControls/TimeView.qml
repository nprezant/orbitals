import QtQuick 2.15
import QtQuick.Controls 2.14

Row {
    property double time
    property bool inEditMode

    spacing: 16

    DetailLabel {
        text: "Time (s)"
    }

    NumberInput {
        text: time
        enabled: inEditMode
    }
}