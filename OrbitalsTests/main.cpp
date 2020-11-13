#include "orbitalsystem.h"
#include <iostream>

int main()
{
  std::cout << "Create empty orbital system\n";

  auto system = OrbitalSystem::Earth();
  std::cout << system.info();

  std::cout << "\nAdd orbital to the system\n";

  system.addOrbital(Orbital::circularRadius(15000, PrimaryBody::Earth()));
  std::cout << system.info();

  std::cout << "\nIncrement time by 10 seconds\n";

  system.incrementTime(10);
  std::cout << system.info();

  return 0;
}
