import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick3D 1.15
import OrbitalsInterface 1.0
import OrbitalChangeData 1.0

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
            // orbitalSpawner.add(0,0,0);
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

        onOrbitalChangeDataListChanged: {
            var orbitalChangeDataList = orbitalsInterface.orbitalChangeDataList;
            orbitalSpawner.update(orbitalChangeDataList);
        }
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
            position: Qt.vector3d(0, 1, 1).times(5250)
            eulerRotation.x: -45
        }

        Model {
            id: primaryBody
            source: "#Cube"
            position: Qt.vector3d(0, 0, 0)
            scale: Qt.vector3d(1, 1, 1).times(1 / bounds.maximum.x).times(637) // radius of earth in km e-1

            materials: [ DefaultMaterial {
                    diffuseColor: "green"
                }
            ]

            SequentialAnimation on eulerRotation {
                loops: Animation.Infinite
                PropertyAnimation {
                    duration: 10000
                    to: Qt.vector3d(0, 0, 0)
                    from: Qt.vector3d(0, -360, 0)
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

        Node {
            id: orbitalSpawner
            property var instances: []
            readonly property int maxInstances: 100

            function add(xPos, yPos, zPos) {
                let orbitalBodyComponent = Qt.createComponent("orbitalbody.qml");
                let instance = orbitalBodyComponent.createObject(
                        orbitalSpawner, { "x": xPos, "y": yPos, "z": zPos, });
                instances.push(instance);
                console.log("created orbital body at " + xPos + ", " + yPos + ", " + zPos);
            }

            function update(orbitalChangeDataList) {
                console.log("length of change list is " + orbitalChangeDataList.length);
                console.log("primary body size " + primaryBody.bounds);
                console.log("primary body size " + primaryBody.bounds.maximum);
                console.log("primary body size " + primaryBody.bounds.minimum);

                for (var i=0; i<orbitalChangeDataList.length; i++)
                {
                    // Add, remove, or update based on change type
                    let orbitalData = orbitalChangeDataList[i];
                    console.log("orbital data = " + orbitalData);
                    console.log("index = " + orbitalData.index);
                    console.log("changeType = " + orbitalData.changeType);
                    console.log("px = " + orbitalData.positionX);
                    console.log("py = " + orbitalData.positionY);
                    console.log("pz = " + orbitalData.positionZ);

                    let changeType = orbitalData.changeType;
                    if (changeType == OrbitalChangeData.Add)
                    {
                        // Create new instance
                        add(orbitalData.positionX / 10, orbitalData.positionY / 10, orbitalData.positionZ / 10);
                    }
                    else if (changeType == OrbitalChangeData.Remove)
                    {
                        // Remove existing instance
                        console.log("not implemented 'remove' yet");
                    }
                    else if (changeType == OrbitalChangeData.Update)
                    {
                        // Update existing instance
                        let guiInstance = instances[i];

                        // km / 10
                        guiInstance.x = orbitalData.positionX / 10;
                        guiInstance.y = orbitalData.positionY / 10;
                        guiInstance.z = orbitalData.positionZ / 10;
                    }
                }
            }
        }
    }
}
