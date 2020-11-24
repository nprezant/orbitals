import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14


ColumnLayout {
    spacing: 16
    Layout.preferredWidth: 230

    ButtonGroup {
        buttons: systemControlButtonsLayout.children
    }

    RowLayout {
        id: systemControlButtonsLayout
        Layout.alignment: Qt.AlignHCenter

        Button {
            text: "Add"
        }

        Button {
            text: "Remove"
        }

        Button {
            text: "Animate"
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
