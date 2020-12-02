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
    DetailLabel {
        text: "theta"
    }

    TextInput {
        text: theta
    }

    DetailLabel {
        text: "Omega"
    }

    TextInput {
        text: bigOmega
    }

    // Row 2
    DetailLabel {
        text: "h"
    }

    TextInput {
        text: h
    }

    DetailLabel {
        text: "inclination"
    }

    TextInput {
        text: inclination
    }

    // Row 3
    DetailLabel {
        text: "e"
    }

    TextInput {
        text: e
    }

    DetailLabel {
        text: "omega"
    }

    TextInput {
        text: omega
    }    
}
