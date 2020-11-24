import QtQuick 2.15 as QQ2
import QtQuick.Window 2.14 as W
import QtQuick.Controls 2.14 as QQControls
import QtQuick3D 1.15 as QQ3D
import QtQuick3D.Helpers 1.15 as Helpers
import Components 1.0 as Components

import OrbitalsInterface 1.0

// To allow gammayray to attach to application, run this:
// echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

W.Window {
    id: window
    width: 1280
    height: 720
    visible: true
    title: qsTr("Orbitals Desktop")

    OrbitalsInterface {
        id: orbitalsInterface

        onOrbitalChangeDataListChanged: {
            var orbitalChangeDataList = orbitalsInterface.orbitalChangeDataList;
            orbitalSpawner.update(orbitalChangeDataList);
        }
    }

    QQ3D.View3D {
        id: view
        anchors.fill: parent
        camera: camera
        renderMode: QQ3D.View3D.Underlay

        environment: QQ3D.SceneEnvironment {
            clearColor: "lightsteelblue"
            backgroundMode: QQ3D.SceneEnvironment.Color
            antialiasingMode: QQ3D.SceneEnvironment.MSAA
            antialiasingQuality: QQ3D.SceneEnvironment.High
        }

        QQ3D.DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -70
        }

        QQ3D.PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 1, 1).times(525)
            eulerRotation.x: -45
        }

        Components.PrimaryBody {
            id: primaryBody
        }

        Components.OrbitalSpawner {
            id: orbitalSpawner
        }

        Helpers.AxisHelper {
            id: axisHelper
            enableAxisLines: true
            enableXYGrid: false
            enableXZGrid: false
            enableYZGrid: false
        }

        Helpers.DebugView {
            id: debugView
            source: parent
            anchors.bottom: parent.bottom
        }
    }

    Components.WasdController {
        id: wasdController
        controlledObject: camera
        focus: true
        speed: 8
        shiftSpeed: 12
    }

    QQ2.Timer {
        interval: 1000 / 60
        running: orbitListView.animateChecked
        repeat: true
        onTriggered: {
            orbitalsInterface.incrementTime();
        }
    }

    QQControls.Label {
        id: countLabel
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 20
        font.pointSize: 20
        font.bold: true
        color: "#848895"
    }

    Components.OrbitListView {
        id: orbitListView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        anchors.topMargin: 10

        onAddButtonClicked: {
            orbitalsInterface.addOrbital();
        }

        onRemoveButtonClicked: {
            if (orbitalSpawner.instances.length > 0)
                orbitalsInterface.removeOrbital(orbitalSpawner.instances.length - 1); // Remove last orbital
        }

        onIncrementButtonClicked: {
            orbitalsInterface.incrementTime()
        }
    }
}
