import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0


ColumnLayout {
    id: root
    spacing: 0
    Layout.preferredWidth: 40
    Layout.alignment: Qt.AlignLeft

    property string name: "New Orbital"
    
    property alias px: orbitalEditorDetails.px
    property alias py: orbitalEditorDetails.py
    property alias pz: orbitalEditorDetails.pz

    property alias vx: orbitalEditorDetails.vx
    property alias vy: orbitalEditorDetails.vy
    property alias vz: orbitalEditorDetails.vz

    Text {
        text: name
    }

    OrbitalEditorDetails {
        id: orbitalEditorDetails
    }
}
