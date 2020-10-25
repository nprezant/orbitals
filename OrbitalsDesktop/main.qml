import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick3D 1.15

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
            orbitalSpawner.add();
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
                    diffuseColor: "blue"
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
            id: orbitalSpawner
            property real range: 300
            property var instances: []
            readonly property int maxInstances: 100

            function add() {
                var xPos = 0 // (2 * Math.random() * range) - range;
                var yPos = 100 // (2 * Math.random() * range) - range;
                var zPos = 0 // (2 * Math.random() * range) - range;

                let orbitalBodyComponent = Qt.createComponent("orbitalbody.qml");
                let instance = orbitalBodyComponent.createObject(
                        orbitalSpawner, { "x": xPos, "y": yPos, "z": zPos, });
                            // "scale": Qt.vector3d(100, 100, 100)});
                // instance.visible = true;
                instances.push(instance);
                countLabel.text = "Models in Scene: " + instances.length;
            }
        }
    }
}
