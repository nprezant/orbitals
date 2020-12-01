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

    columnSpacing: 16
    rowSpacing: 16
    columns: 4
    clip: true

    // Row 1
    Text {
        text: "theta"
    }

    TextInput {
        text: theta
    }

    Text {
        text: "Omega"
    }

    TextInput {
        text: bigOmega
    }

    // Row 2
    Text {
        text: "h"
    }

    TextInput {
        text: h
    }

    Text {
        text: "inclination"
    }

    TextInput {
        text: inclination
    }

    // Row 3
    Text {
        text: "e"
    }

    TextInput {
        text: e
    }

    Text {
        text: "omega"
    }

    TextInput {
        text: omega
    }    
}
