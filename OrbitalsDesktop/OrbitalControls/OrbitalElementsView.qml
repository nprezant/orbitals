import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

GridLayout {

    property double theta
    property double h
    property double e

    property double bigOmega
    property double inclination
    property double omega

    property bool inEditMode

    columnSpacing: 16
    rowSpacing: 16
    columns: 4
    clip: true

    // Row 1
    DetailLabel {
        text: "theta"
    }

    NumberInput {
        text: theta
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    DetailLabel {
        text: "Omega"
    }

    NumberInput {
        text: bigOmega
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    // Row 2
    DetailLabel {
        text: "h"
    }

    NumberInput {
        text: h
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    DetailLabel {
        text: "inclination"
    }

    NumberInput {
        text: inclination
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    // Row 3
    DetailLabel {
        text: "e"
    }

    NumberInput {
        text: e
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }

    DetailLabel {
        text: "omega"
    }

    NumberInput {
        text: omega
        enabled: inEditMode
        Layout.minimumWidth: suggestedMinimumWidth
        Layout.fillWidth: true
    }    
}
