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

    property alias theta: orbitalEditorDetails.theta
    property alias h: orbitalEditorDetails.h
    property alias e: orbitalEditorDetails.e

    property alias bigOmega: orbitalEditorDetails.bigOmega
    property alias inclination: orbitalEditorDetails.inclination
    property alias omega: orbitalEditorDetails.omega

    property double time

    implicitWidth: column.implicitWidth
    implicitHeight: column.implicitHeight

    color: "#b195bf"
    border.color: "#D9FFFFFF"
    radius: 5

    Column {
        id: column
        padding: 10
        spacing: 5

        Text {
            text: name
            topPadding: 5
            bottomPadding: 5

            MouseArea {
                anchors.fill: parent
                anchors.margins: -column.padding
                onClicked: {
                    orbitalEditorDetails.state == "show" ? orbitalEditorDetails.state = "hide" : orbitalEditorDetails.state = "show";
                }
            }
        }

        OrbitalEditorDetails {
            id: orbitalEditorDetails
            scale: 0.0

            height: 0
            width: 0
            state: "hide"

            states: [
                State {
                    name: "show"
                    PropertyChanges {
                        target: orbitalEditorDetails;
                        width: implicitWidth;
                        height: implicitHeight;
                        scale: 1.0;
                        opacity: 1.0;
                    }
                },
                State {
                    name: "hide"
                    PropertyChanges {
                        target: orbitalEditorDetails;
                        width: 0.0;
                        height: 0.0;
                        scale: 0.0;
                        opacity: 0.0;
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "show"
                    to: "hide"
                    reversible: true
                    NumberAnimation { target: orbitalEditorDetails; properties: "opacity,scale,width,height"; duration: 200; }
                }
            ]
        }
    }
}
