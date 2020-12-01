import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14

import OrbitalsInterface 1.0

ListView {
    id: listView
    clip: true
    spacing: 16

    model: ListModel {}
    delegate: OrbitalEditor {
        name: model.name
        px: model.px
        py: model.py
        pz: model.pz
        vx: model.vx
        vy: model.vy
        vz: model.vz

        theta: model.theta
        h: model.h
        e: model.e
        bigOmega: model.Omega
        inclination: model.inclination
        omega: model.omega

        time: model.time
    }

    // ScrollBar.vertical: ScrollBar {
    //     parent: frame
    //     policy: ScrollBar.AlwaysOn
    //     anchors.top: parent.top
    //     anchors.topMargin: frame.topPadding
    //     anchors.right: parent.right
    //     anchors.rightMargin: 1
    //     anchors.bottom: parent.bottom
    //     anchors.bottomMargin: frame.bottomPadding
    // }

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
        return {
            name: "New Orbital",
            px: Math.round(orbitalChangeData.positionX),
            py: Math.round(orbitalChangeData.positionY),
            pz: Math.round(orbitalChangeData.positionZ),
            vx: Math.round(orbitalChangeData.velocityX),
            vy: Math.round(orbitalChangeData.velocityY),
            vz: Math.round(orbitalChangeData.velocityZ),

            theta: Math.round(orbitalChangeData.theta * 180. / Math.PI),
            h: Math.round(orbitalChangeData.h),
            e: Math.round(orbitalChangeData.e),
            Omega: Math.round(orbitalChangeData.Omega),
            inclination: Math.round(orbitalChangeData.inclination),
            omega: Math.round(orbitalChangeData.omega),

            time: Math.round(orbitalChangeData.time),
        };
    }
}