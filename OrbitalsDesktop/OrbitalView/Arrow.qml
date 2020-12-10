import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Materials 1.15

Node {
    property double scaleFactor: 0.3
    property double spacing: 10
    property var color: "red"

    readonly property var xAxis: Qt.vector3d(1, 0, 0)
    readonly property var yAxis: Qt.vector3d(0, 1, 0)
    readonly property var zAxis: Qt.vector3d(0, 0, 1)

    property var orientation: Qt.vector3d(0, 1, 0)
    // property double xRotation
    // property double yRotation
    // property double zRotation

    // onOrientationChanged: {
    //     console.log(orientation)
    //     parent.xRotation = Math.acos(orientation.dotProduct(xAxis) / orientation.length);
    //     parent.yRotation = Math.acos(orientation.dotProduct(yAxis) / orientation.length);
    //     parent.zRotation = Math.acos(orientation.dotProduct(zAxis) / orientation.length);

    //     console.log(xRotation);
    //     console.log(yRotation);
    //     console.log(zRotation);
    // }

    Model {
        id: cylinder
        // eulerRotation.x: parent.xRotation
        // eulerRotation.y: parent.yRotation
        // eulerRotation.z: parent.zRotation
        property double sourceHeight: bounds.maximum.minus(bounds.minimum).dotProduct(Qt.vector3d(0, 1, 0)) // should be 100 for built in models
        property double height: sourceHeight * scale.y
        source: "#Cylinder"
        scale: Qt.vector3d(0.2, 1, 0.2).times(scaleFactor)
        y: parent.y + spacing + height / 2 

        materials: [ 
            DefaultMaterial
            {
                diffuseColor: parent.parent.color
            }
        ]
    }

    Model {
        source: "#Cone"
        scale: Qt.vector3d(0.5, 1, 0.5).times(1.2).times(parent.scaleFactor)
        y: cylinder.y + cylinder.height / 2

        materials: [ 
            DefaultMaterial
            {
                diffuseColor: parent.parent.color
            }
        ]
    }
}