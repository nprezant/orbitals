import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

Row {
    property alias px: positionVelocityView.px
    property alias py: positionVelocityView.py
    property alias pz: positionVelocityView.pz

    property alias vx: positionVelocityView.vx
    property alias vy: positionVelocityView.vy
    property alias vz: positionVelocityView.vz

    property alias theta: orbitalElementsView.theta
    property alias h: orbitalElementsView.h
    property alias e: orbitalElementsView.e

    property alias bigOmega: orbitalElementsView.bigOmega
    property alias inclination: orbitalElementsView.inclination
    property alias omega: orbitalElementsView.omega

    spacing: 10

    ButtonGroup {
        buttons: buttonLayout.children
    }

    Column {
        id: buttonLayout
        spacing: 4
        padding: 2
        property int sideLength: 20
        Button {
            // TODO change to images, like so
            // Image {
            //     anchors.fill: parent
            //     source: "qrc:/icons/positionVelocity.png"
            // }
            text: "1"
            width: parent.sideLength
            height: parent.sideLength
            checkable: true
            checked: true
            onClicked: { detailView.state = "pv" }
        }
        Button {
            text: "2"
            width: parent.sideLength
            height: parent.sideLength
            checkable: true
            onClicked: { detailView.state = "el" }
        }
    }

    Column {
        id: detailView
        state: "pv"

        PositionVelocityView {
            id: positionVelocityView
        }

        OrbitalElementsView {
            id: orbitalElementsView
        }

        states: [
            State {
                name: "pv"
                PropertyChanges {
                    target: positionVelocityView;
                    height: positionVelocityView.implicitHeight;
                    width: positionVelocityView.implicitWidth;
                    opacity: 1;
                }
                PropertyChanges {
                    target: orbitalElementsView;
                    height: 0;
                    width: positionVelocityView.implicitWidth;
                    opacity: 0;
                }
            },
            State {
                name: "el"
                PropertyChanges {
                    target: positionVelocityView;
                    height: 0;
                    width: orbitalElementsView.implicitWidth;
                    opacity: 0;
                }
                PropertyChanges {
                    target: orbitalElementsView;
                    height: orbitalElementsView.implicitHeight;
                    width: orbitalElementsView.implicitWidth;
                    opacity: 1;
                }
            }
        ]

        transitions: [
            Transition {
                from: "pv"
                to: "el"
                reversible: true
                NumberAnimation { targets: [positionVelocityView, orbitalElementsView]; properties: "width,height,opacity"; duration: 200 }
            }
        ]
    }
}
