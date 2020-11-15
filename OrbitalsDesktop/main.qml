import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick3D 1.15
import OrbitalsInterface 1.0

Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Orbitals Desktop")

    Button {
        id: addButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        text: "Add Orbital"
        implicitWidth: 150

        background: Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }

        onClicked: {
            cubeSpawner.add();
            orbitalsInterface.addOrbital();
        }
    }

    Label {
        id: countLabel
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        font.pointSize: 20
        font.bold: true
        color: "#848895"
    }

    Button {
        id: removeButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        text: "Remove Orbital"
        implicitWidth: 150
        enabled: false

        background: Rectangle {
            implicitWidth: 150
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: parent.down ? "#6b7080" : "#848895"
            border.color: "#222840"
            border.width: 1
            radius: 5
        }

        onClicked: {
            if (cubeSpawner.instances.length > 0)
                cubeSpawner.remove();
        }
    }

    Button {
        id: incrementTimeButton
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        anchors.topMargin: 80
        text: "Increment Time"
        implicitWidth: 150
        enabled: true

        background: Rectangle {
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

    OrbitalsInterface {
        id: orbitalsInterface
    }

    View3D {
        id: view
        anchors.fill: parent
        camera: camera
        renderMode: View3D.Underlay

        environment: SceneEnvironment {
            clearColor: "yellow"
            backgroundMode: SceneEnvironment.Color
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }

        PerspectiveCamera {
            position: Qt.vector3d(0, 200, 300)
            eulerRotation.x: -30
        }

        Model {
            source: "#Sphere"
            position: Qt.vector3d(0, 150, 0)

            materials: [ DefaultMaterial {
                    diffuseColor: "green"
                }
            ]

            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation {
                    duration: 3000
                    to: -150
                    from: 150
                    easing.type:Easing.InQuad
                }
                NumberAnimation {
                    duration: 3000
                    to: 150
                    from: -150
                    easing.type:Easing.OutQuad
                }
            }
        }

        Node {
            id: cubeSpawner
            property var instances: []
            readonly property int maxInstances: 100

            function add() {
                var xPos = 0
                var yPos = 100
                var zPos = 0

                let cubeComponent = Qt.createComponent("orbitalbody.qml");
                let instance = cubeComponent.createObject(
                        cubeSpawner, { "x": xPos, "y": yPos, "z": zPos, });
                            // "scale": Qt.vector3d(100, 100, 100)});
                instances.push(instance);
                updateButtonState();
            }

            function remove() {
                // Remove last item in instances list
                let instance = instances.pop();
                instance.destroy();
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
                countLabel.text = "Cubes in Scene: " + instances.length + "; Name: " + orbitalsInterface.systemName;
            }
        }
    }
}
