#include "orbitalsystem.h"
#include <iostream>

int main()
{
  std::cout << "Running orbits...\n";

  auto system = OrbitalSystem::Earth();
  std::cout << system.info();

  system.addOrbital(Orbital::circularRadius(15000, PrimaryBody::Earth()));
  std::cout << system.info();

  return 0;
}
