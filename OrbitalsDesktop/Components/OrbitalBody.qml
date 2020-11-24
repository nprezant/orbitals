import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15

Node {
    id: root

    property real xRotation: Math.random() * (360 - (-360)) + -360
    property real yRotation: Math.random() * (360 - (-360)) + -360
    property real zRotation: Math.random() * (360 - (-360)) + -360

    Model {
        source: "#Cube"
        // scale: Qt.vector3d(150, 150, 150)
        eulerRotation.x: 90

        SequentialAnimation on eulerRotation {
            loops: Animation.Infinite
            PropertyAnimation {
                duration: Math.random() * (10000 - 1) + 1000
                to: Qt.vector3d(xRotation -  360, yRotation - 360, zRotation - 360)
                from: Qt.vector3d(xRotation, yRotation, zRotation)
            }
        }

        materials: [ 
            DefaultMaterial
            {
                diffuseColor: "blue"
            }
        ]
    }
}
