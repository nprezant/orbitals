import QtQuick 2.15 as QQ2
import QtQuick.Window 2.14 as W
import QtQuick.Controls 2.14 as QQControls
import QtQuick3D 1.15 as QQ3D
import QtQuick3D.Helpers 1.15 as Helpers
import Components 1.0 as Components

import OrbitalsInterface 1.0

// To allow gammayray to attach to application, run this:
// echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

W.Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Orbitals Desktop")

    OrbitalsInterface {
        id: orbitalsInterface

        onOrbitalChangeDataListChanged: {
            var orbitalChangeDataList = orbitalsInterface.orbitalChangeDataList;
            orbitalSpawner.update(orbitalChangeDataList);
        }
    }

    QQ3D.View3D {
        id: view
        anchors.fill: parent
        camera: camera
        renderMode: QQ3D.View3D.Underlay

        environment: QQ3D.SceneEnvironment {
            clearColor: "lightsteelblue"
            backgroundMode: QQ3D.SceneEnvironment.Color
            antialiasingMode: QQ3D.SceneEnvironment.MSAA
            antialiasingQuality: QQ3D.SceneEnvironment.High
        }

        QQ3D.DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }

        QQ3D.PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 1, 1).times(5250)
            eulerRotation.x: -45
            // lookAt: Qt.vector3d(0,0,0)
        }

        QQ3D.Model {
            id: primaryBody
            source: "#Cube"
            position: Qt.vector3d(0, 0, 0)
            scale: Qt.vector3d(1, 1, 1).times(1 / bounds.maximum.x).times(637) // radius of earth in km e-1

            materials: [ QQ3D.DefaultMaterial {
                    diffuseColor: "green"
                }
            ]

            QQ2.SequentialAnimation on eulerRotation {
                loops: QQ2.Animation.Infinite
                QQ2.PropertyAnimation {
                    duration: 10000
                    to: Qt.vector3d(0, 0, 0)
                    from: Qt.vector3d(0, -360, 0)
                }
            }
        }

        QQ3D.Node {
            id: orbitalSpawner
            property var instances: []
            readonly property int maxInstances: 100

            function update(orbitalChangeDataList) {

                // TODO sanity check list lengths
                for (var i=0; i<orbitalChangeDataList.length; i++)
                {
                    // Add, remove, or update based on change type
                    let orbitalData = orbitalChangeDataList[i];

                    let changeType = orbitalData.changeType;
                    if (changeType === OrbitalChangeData.Add)
                    {
                        // Create new instance
                        let xPos = orbitalData.positionX / 10;
                        let yPos = orbitalData.positionY / 10;
                        let zPos = orbitalData.positionZ / 10;
                        let orbitalBodyComponent = Qt.createComponent("orbitalbody.qml");
                        let instance = orbitalBodyComponent.createObject(
                            orbitalSpawner, { "x": xPos, "y": yPos, "z": zPos, });
                        instances.push(instance);
                    }
                    else if (changeType === OrbitalChangeData.Remove)
                    {
                        // Remove existing instance
                        let index = orbitalData.index;

                        let instance = instances[index];
                        instance.destroy();

                        // Splice is a fancy way to remove by "splicing in" at the index position,
                        // removing 1 item, then not adding any others
                        instances.splice(index, 1);
                    }
                    else if (changeType === OrbitalChangeData.Update)
                    {
                        // Update existing instance
                        let guiInstance = instances[i];

                        // km / 10
                        guiInstance.x = orbitalData.positionX / 10;
                        guiInstance.y = orbitalData.positionY / 10;
                        guiInstance.z = orbitalData.positionZ / 10;
                    }
                }
                updateButtonState();
            }

            function updateButtonState() {
                if (instances.length === 0)
                {
                    addButton.enabled = true;
                    removeButton.enabled = false;
                }
                else if (instances.length === maxInstances)
                {
                    addButton.enabled = false;
                    removeButton.enabled = true;
                }
                else
                {
                    addButton.enabled = true;
                    removeButton.enabled = true;
                }
                countLabel.text = "Orbitals in Scene: " + instances.length + "; System name: " + orbitalsInterface.systemName;
            }
        }
        Helpers.AxisHelper {
            id: axisHelper
            enableAxisLines: true
        }

        Helpers.DebugView {
            id: debugView
            source: parent
            anchors.bottom: parent.bottom
        }
    }

    Components.WasdController {
        id: wasdController
        controlledObject: camera
        focus: true
        speed: 8
        shiftSpeed: 12
    }

    QQ2.Timer {
        interval: 1000 / 60
        running: startStopCheckBox.checked ? true : false
        repeat: true
        onTriggered: {
            orbitalsInterface.incrementTime();
        }
    }

    QQControls.CheckBox {
        id: startStopCheckBox
        checked: false
        anchors.left: parent.left
        anchors.top: incrementTimeButton.top
        anchors.margins: 20
        anchors.topMargin: 60
        text: "Start animation"


        background: QQ2.Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: 1
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }
    }

    QQControls.Button {
        id: addButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        text: "Add Orbital"
        implicitWidth: 150

        background: QQ2.Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }

        onClicked: {
            orbitalsInterface.addOrbital();
        }
    }

    QQControls.Label {
        id: countLabel
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        font.pointSize: 20
        font.bold: true
        color: "#848895"
    }

    QQControls.Button {
        id: removeButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        text: "Remove Orbital"
        implicitWidth: 150
        enabled: false

        background: QQ2.Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }

        onClicked: {
            if (orbitalSpawner.instances.length > 0)
            {
                orbitalsInterface.removeOrbital(orbitalSpawner.instances.length - 1); // Remove last orbital
            }
        }
    }

    QQControls.Button {
        id: incrementTimeButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        anchors.topMargin: 80
        text: "Increment Time"
        implicitWidth: 150
        enabled: true

        background: QQ2.Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }

        onClicked: {
            orbitalsInterface.incrementTime();
        }
    }

    Components.OrbitListView {
        id: orbitListView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        anchors.topMargin: 200
    }
}
