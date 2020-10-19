#include "orbitalsystem.h"
#include <string>

std::string OrbitalSystem::info()
{
  std::string primaryBodyMsg = "Primary body: " + primarybody_.name + "\n";

  auto numOrbitals = std::to_string(static_cast<int>(orbitals_.size()));
  std::string numOrbitalMsg = "num orbitals: " + numOrbitals + "\n";

  return primaryBodyMsg + numOrbitalMsg;
}
