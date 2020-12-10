import QtQuick 2.15
import QtQuick3D 1.15

import OrbitalsInterface 1.0

Node {

    property var instances: []

    function update(orbitalChangeDataList) {

        // TODO sanity check list lengths
        for (var i=0; i<orbitalChangeDataList.length; i++) {

            // Add, remove, or update based on change type
            let orbitalData = orbitalChangeDataList[i];
            let changeType = orbitalData.changeType;

            if (changeType === OrbitalChangeData.Add) {
                // Create new instance
                let xPos = orbitalData.positionX / 100;
                let yPos = orbitalData.positionY / 100;
                let zPos = orbitalData.positionZ / 100;
                let orbitalBodyComponent = Qt.createComponent("OrbitalBody.qml");
                let instance = orbitalBodyComponent.createObject(
                    parent, { "x": xPos, "y": yPos, "z": zPos, });
                instances.push(instance);
            }
            else if (changeType === OrbitalChangeData.Remove) {
                // Remove existing instance
                let index = orbitalData.index;
                let instance = instances[index];
                instance.destroy();

                // Splice is a fancy way to remove by "splicing in" at the index position,
                // removing 1 item, then not adding any others
                instances.splice(index, 1);
            }
            else if (changeType === OrbitalChangeData.Update) {
                // Update existing instance
                let guiInstance = instances[orbitalData.index];

                // km / 100
                guiInstance.x = orbitalData.positionX / 100;
                guiInstance.y = orbitalData.positionY / 100;
                guiInstance.z = orbitalData.positionZ / 100;

                // km/s / 100
                guiInstance.velocity.x = orbitalData.velocityX / 100;
                guiInstance.velocity.y = orbitalData.velocityY / 100;
                guiInstance.velocity.z = orbitalData.velocityZ / 100;
            }
        }
    }
}