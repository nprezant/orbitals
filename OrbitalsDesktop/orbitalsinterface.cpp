#include "orbitalsinterface.h"

QString OrbitalsInterface::systemName() const
{
    return systemName_;
}

void OrbitalsInterface::setSystemName(const QString& newName)
{
    systemName_ = newName;
}
