import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0


ColumnLayout {
    id: root
    spacing: 16
    Layout.preferredWidth: 230

    signal addButtonClicked()
    signal removeButtonClicked()
    signal incrementButtonClicked()

    property bool animateChecked: false
    property bool canAdd: true
    property bool canRemove: false

    readonly property int maxInstances: 100

    Component.onCompleted: {
        addButton.clicked.connect(root.addButtonClicked)
        removeButton.clicked.connect(root.removeButtonClicked)
        incrementButton.clicked.connect(root.incrementButtonClicked)
    }

    ButtonGroup {
        buttons: buttonLayout.children
    }

    RowLayout {
        id: buttonLayout
        Layout.alignment: Qt.AlignHCenter

        Button {
            id: addButton
            text: "Add"
            enabled: root.canAdd
        }

        Button {
            id: removeButton
            text: "Remove"
            enabled: canRemove
        }

        Button {
            id: incrementButton
            text: "+time"
        }

        Switch {
            // A really dumb way to handle checked/unchecked state
            id: animateSwitch
            text: "Animate"
            function isChecked() { return root.animateChecked }
            checked: isChecked();
            onClicked: {
                root.animateChecked = !root.animateChecked;
                checked = Qt.binding(isChecked);
            }
        }
    }

    Frame {
        id: frame
        leftPadding: 1
        rightPadding: 1

        Layout.fillWidth: true
        Layout.fillHeight: true
        implicitHeight: 300

        background: Rectangle {
            color: "lightgreen"
            border.color: "#21be2b"
            radius: 10
        }        

        ListView {
            id: listView
            clip: true
            anchors.fill: parent
            model: ListModel {}
            delegate: ItemDelegate {
                text: model.name + ", x: " + model.x  + ", y: " + model.y + ", z: " + model.z
                width: listView.width
            }

            ScrollBar.vertical: ScrollBar {
                parent: filesFrame
                policy: ScrollBar.AlwaysOn
                anchors.top: parent.top
                anchors.topMargin: filesFrame.topPadding
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: filesFrame.bottomPadding
            }

            function addOrbital(orbitalChangeData) {
                model.append(extractOrbitalInfo(orbitalChangeData));
            }

            function removeOrbital(index) {
                model.remove(index, 1);
            }

            function updateOrbital(orbitalChangeData) {
                let index = orbitalChangeData.index;
                model.set(
                    index,
                    extractOrbitalInfo(orbitalChangeData)
                );
            }

            function extractOrbitalInfo(orbitalChangeData) {
                let xPos = Math.round(orbitalChangeData.positionX);
                let yPos = Math.round(orbitalChangeData.positionY);
                let zPos = Math.round(orbitalChangeData.positionZ);
                let info = {
                    name: "Name tbd",
                    x: xPos,
                    y: yPos,
                    z: zPos,
                    vx: 0,
                    vy: 0,
                    vz: 0,
                };
                return info;
            }
        }
    }

    function update(orbitalChangeDataList) {

        for (var i=0; i<orbitalChangeDataList.length; i++) {

            // Add, remove, or update based on change type
            let orbitalChangeData = orbitalChangeDataList[i];
            let changeType = orbitalChangeData.changeType;

            if (changeType === OrbitalChangeData.Add) {
                // Add new item to list view
                listView.addOrbital(orbitalChangeData);
            }
            else if (changeType === OrbitalChangeData.Remove) {
                // Remove existing instance
                listView.removeOrbital(orbitalChangeData.index);
            }
            else if (changeType === OrbitalChangeData.Update) {
                // Update existing instance
                listView.updateOrbital(orbitalChangeData)
            }
        }
        updateButtonState();
    }

    function updateButtonState() {
        let numOrbitals = listView.model.count;
        if (numOrbitals === 0)
        {
            canAdd = true;
            canRemove = false;
        }
        else if (numOrbitals === maxInstances)
        {
            canAdd = false;
            canRemove = true;
        }
        else
        {
            canAdd = true;
            canRemove = true;
        }
        countLabel.text = "Orbitals in Scene: " + numOrbitals
    }
}
