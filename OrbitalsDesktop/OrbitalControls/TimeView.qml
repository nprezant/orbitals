import QtQuick 2.15
import QtQuick.Controls 2.14

Row {
    property double time

    spacing: 16

    DetailLabel {
        text: "Time"
    }

    TextInput {
        text: time
    }
}