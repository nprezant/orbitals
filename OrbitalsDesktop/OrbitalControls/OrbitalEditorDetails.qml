import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

Column {
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

    property alias time: timeView.time

    spacing: 10

    EditButtons {
        id: editButtons
        layoutDirection: Qt.RightToLeft
        width: parent.width
    }

    Row {
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
            Button {
                text: "3"
                width: parent.sideLength
                height: parent.sideLength
                checkable: true
                onClicked: { detailView.state = "time" }
            }
        }

        Column {
            id: detailView
            state: "pv"

            PositionVelocityView {
                id: positionVelocityView
                inEditMode: editButtons.inEditMode
            }

            OrbitalElementsView {
                id: orbitalElementsView
                inEditMode: editButtons.inEditMode
            }

            TimeView {
                id: timeView
                inEditMode: editButtons.inEditMode
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
                    PropertyChanges {
                        target: timeView;
                        height: 0;
                        width: positionVelocityView.implicitWidth;
                        opacity: 0;
                    }
                },
                State {
                    name: "el"
                    PropertyChanges {
                        target: orbitalElementsView;
                        height: orbitalElementsView.implicitHeight;
                        width: orbitalElementsView.implicitWidth;
                        opacity: 1;
                    }
                    PropertyChanges {
                        target: positionVelocityView;
                        height: 0;
                        width: orbitalElementsView.implicitWidth;
                        opacity: 0;
                    }
                    PropertyChanges {
                        target: timeView;
                        height: 0;
                        width: orbitalElementsView.implicitWidth;
                        opacity: 0;
                    }
                },
                State {
                    name: "time"
                    PropertyChanges {
                        target: timeView;
                        height: timeView.implicitHeight;
                        width: timeView.implicitWidth;
                        opacity: 1;
                    }
                    PropertyChanges {
                        target: positionVelocityView;
                        height: 0;
                        width: timeView.implicitWidth;
                        opacity: 0;
                    }
                    PropertyChanges {
                        target: orbitalElementsView;
                        height: 0;
                        width: timeView.implicitWidth;
                        opacity: 0;
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "*"
                    to: "*"
                    NumberAnimation { targets: [positionVelocityView, orbitalElementsView, timeView]; properties: "width,height,opacity"; duration: 200 }
                }
            ]
        }
    }
}
