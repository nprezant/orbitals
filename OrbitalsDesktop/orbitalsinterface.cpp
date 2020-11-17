#include "orbitalsinterface.h"
#include <iostream>

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
    std::cout << "adding orbital" << "\n";
    orbitalSystem_.addCircularOrbitRadius(10000);
    std::cout << orbitalSystem_.info() << std::endl;
}

void OrbitalsInterface::incrementTime()
{
    std::cout << "incrementing time" << "\n";
    orbitalSystem_.incrementTime(10);
    std::cout << orbitalSystem_.info() << std::endl;

    orbitalChangeDataVector_.clear();
    int index = 0;
    
    for (const auto& orbital : orbitalSystem_)
    {
        const auto position = orbital.position();

        orbitalChangeDataVector_.append(new OrbitalChangeData(
            index,
            OrbitalChangeData::Update,
            position.X,
            position.Y,
            position.Z
        ));

        index++;
    }

    // Emit signal that the orbital system changed
    orbitalChangeDataListChanged();
}
