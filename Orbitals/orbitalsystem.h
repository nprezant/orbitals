#ifndef ORBITALSYSTEM_H
#define ORBITALSYSTEM_H

#include <vector>

#include "orbital.h"
#include "primarybody.h"

class OrbitalSystem
{
  PrimaryBody primaryBody_;
  std::vector<Orbital> orbitals_;

  OrbitalSystem(PrimaryBody primaryBody, std::vector<Orbital> orbitals)
      : primaryBody_(primaryBody), orbitals_(orbitals)
  {
  }

public:
  // Center around earth with no default orbits
  static OrbitalSystem Earth()
  {
    return OrbitalSystem(PrimaryBody::Earth(), {});
  }

  // Add an existing orbital to this system.
  void addOrbital(Orbital& orbital);

  // Information on this orbital system
  std::string info();
};

#endif // ORBITALSYSTEM_H
