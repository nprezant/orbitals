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

    // OrbitalChangeData* o = new OrbitalChangeData();
    auto index = 0;
    auto changeType = OrbitalChangeData::ChangeType::Update;
    auto px = 1.0;
    auto py = 2.0;
    auto pz = 3.0;
    orbitalChangeDataVector_.append(new OrbitalChangeData(index, changeType, px, py, pz));

    // Emit signal that the orbital system changed
    orbitalChangeDataListChanged();
}
