import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

Row {
    property bool inEditMode: state == "editMode"
    property double buttonLength: 20

    spacing: 5

    Button {
        id: editButton
        text: "e"
        width: parent.buttonLength
        height: parent.buttonLength
        onClicked: { parent.state = "editMode" }
    }
    Button {
        id: noButton
        text: "n"
        width: 0
        height: parent.buttonLength
        onClicked: { parent.state = "" }
    }
    Button {
        id: yesButton
        text: "y"
        width: 0
        height: parent.buttonLength
        onClicked: { parent.state = "" }
    }

    states: [
        State {
            name: "editMode"
            PropertyChanges {
                target: editButton;
                width: 0;
                opacity: 0;
            }
            PropertyChanges {
                target: noButton;
                width: parent.buttonLength;
                opacity: 1;
            }
            PropertyChanges {
                target: yesButton;
                width: parent.buttonLength;
                opacity: 1;
            }
        }
    ]

    transitions: [
            Transition {
                from: ""
                to: "editMode"
                reversible: true
                NumberAnimation { targets: [editButton, noButton, yesButton]; properties: "width,opacity"; duration: 200 }
            }
        ]
}