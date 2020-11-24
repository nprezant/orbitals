import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14


ColumnLayout {
    id: root
    spacing: 16
    Layout.preferredWidth: 230

    signal addButtonClicked()
    signal removeButtonClicked()
    signal incrementButtonClicked()
    property bool animateChecked: false

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
        }

        Button {
            id: removeButton
            text: "Remove"
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
        id: filesFrame
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
            id: filesListView
            clip: true
            anchors.fill: parent
            model: ListModel {
                Component.onCompleted: {
                    for (var i = 0; i < 20; ++i) {
                        append({
                            author: "Author",
                            album: "Album",
                            track: "Track 0" + (i % 9 + 1),
                        });
                    }
                }
            }
            delegate: ItemDelegate {
                text: model.author + " - " + model.album + " - " + model.track
                width: filesListView.width
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
        }
    }
}
