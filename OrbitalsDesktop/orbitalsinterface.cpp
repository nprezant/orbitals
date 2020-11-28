#include "orbitalsinterface.h"
#include <iostream>
#include <stdlib.h> // rand

QString OrbitalsInterface::systemName() const
{
    return systemName_;
}

void OrbitalsInterface::setSystemName(const QString& newName)
{
    systemName_ = newName;
}

void OrbitalsInterface::addOrbital()
{
    const auto r = rand() % 10000 + 1; // Number between 0 and 10000
    orbitalSystem_.addCircularOrbitRadius(9000 + r);

    const auto index = orbitalSystem_.size() - 1;
    auto orbital = orbitalSystem_[index];
    const auto position = orbital.position();
    const auto velocity = orbital.velocity();

    orbitalChangeDataVector_.clear();
    orbitalChangeDataVector_.append(new OrbitalChangeData(
        0, // Index N/A for adding
        OrbitalChangeData::Add,
        position,
        velocity
    ));

    // Emit signal that the orbital system changed
    orbitalChangeDataListChanged();
}

void OrbitalsInterface::removeOrbital(int index)
{
    orbitalSystem_.removeOrbital(index);

    orbitalChangeDataVector_.clear();
    orbitalChangeDataVector_.append(new OrbitalChangeData(
        index,
        OrbitalChangeData::Remove,
        Vector3(0, 0, 0), // Position N/A for removing
        Vector3(0, 0, 0) // Velocity N/A for removing
    ));

    // Emit signal that the orbital system changed
    orbitalChangeDataListChanged();
}

void OrbitalsInterface::incrementTime()
{
    orbitalSystem_.incrementTime(20);

    orbitalChangeDataVector_.clear();
    int index = 0;

    for (const auto& orbital : orbitalSystem_)
    {
        const auto position = orbital.position();
        const auto velocity = orbital.velocity();

        orbitalChangeDataVector_.append(new OrbitalChangeData(
            index,
            OrbitalChangeData::Update,
            position,
            velocity
        ));

        index++;
    }

    // Emit signal that the orbital system changed
    orbitalChangeDataListChanged();
}
