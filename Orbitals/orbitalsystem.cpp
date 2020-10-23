#include "orbitalsystem.h"
#include <string>

void OrbitalSystem::addOrbital(Orbital orbital)
{
  orbital.setPrimaryBody(primaryBody_);
  orbitals_.push_back(orbital);
}

std::string OrbitalSystem::info()
{
  std::string primaryBodyMsg = "Primary body: " + primaryBody_.name + "\n";

  auto numOrbitals = std::to_string(static_cast<int>(orbitals_.size()));
  std::string numOrbitalMsg = "num orbitals: " + numOrbitals + "\n";

  return primaryBodyMsg + numOrbitalMsg;
}
