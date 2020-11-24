import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15

Node {
    id: root

    Model {
        id: primaryBody
        source: "#Cube"
        position: Qt.vector3d(0, 0, 0)
        scale: Qt.vector3d(1, 1, 1).times(1 / bounds.maximum.x).times(63.7) // radius of earth in km e-1

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
}