import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

Rectangle {
    property string name: "New Orbital"

    property alias px: orbitalEditorDetails.px
    property alias py: orbitalEditorDetails.py
    property alias pz: orbitalEditorDetails.pz

    property alias vx: orbitalEditorDetails.vx
    property alias vy: orbitalEditorDetails.vy
    property alias vz: orbitalEditorDetails.vz   

    implicitWidth: layout.width
    implicitHeight: layout.height
    color: "#40000000"
    border.color: "#D9FFFFFF"
    radius: 5

    ColumnLayout {
        id: layout
        spacing: 0
        Layout.preferredWidth: 40
        Layout.alignment: Qt.AlignLeft        

        Text {
            text: name
            Layout.margins: 10
            
            MouseArea {
                anchors.fill: parent
                anchors.margins: -10
                onClicked: {
                    orbitalEditorDetails.visible = !orbitalEditorDetails.visible;
                }
            }
        }

        OrbitalEditorDetails {
            id: orbitalEditorDetails
            visible: false
            Layout.margins: 10
        }
    }
}
