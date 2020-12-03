import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

GridLayout {

    property double px
    property double py
    property double pz

    property double vx
    property double vy
    property double vz

    property bool inEditMode

    columnSpacing: 16
    rowSpacing: 16
    columns: 4
    clip: true

    // Row 1
    Text {
        // Blank top left table cell
    }

    DetailLabel {
        text: "x"
    }

    DetailLabel {
        text: "y"
    }

    DetailLabel {
        text: "z"
    }

    // Row 2
    DetailLabel {
        text: "Position (km)"
    }

    NumberInput {
        text: px
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    NumberInput {        
        text: py
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    NumberInput {
        text: pz
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    // Row 3
    DetailLabel {
        text: "Velocity (km/s)"
    }

    NumberInput {
        text: vx
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
        enabled: inEditMode
    }

    NumberInput {
        text: vy
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    NumberInput {
        text: vz
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }    
}
