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

void OrbitalsInterface::incrementTime()
{
    std::cout << "incrementing time";
}
