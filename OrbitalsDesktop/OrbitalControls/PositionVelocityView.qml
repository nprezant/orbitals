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

    TextInput {
        text: px
    }

    TextInput {
        text: py
    }

    TextInput {
        text: pz
    }

    // Row 3
    DetailLabel {
        text: "Velocity (km/s)"
    }

    TextInput {
        text: vx
    }

    TextInput {
        text: vy
    }

    TextInput {
        text: vz
    }    
}
