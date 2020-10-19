#ifndef ORBITALSYSTEM_H
#define ORBITALSYSTEM_H

#include <vector>

#include "orbital.h"
#include "primarybody.h"

class OrbitalSystem
{
  PrimaryBody primarybody_;
  std::vector<Orbital> orbitals_;

  OrbitalSystem(PrimaryBody primaryBody, std::vector<Orbital> orbitals)
      : primarybody_(primaryBody), orbitals_(orbitals)
  {
  }

public:
  // Center around earth with no default orbits
  static OrbitalSystem Earth()
  {
    return OrbitalSystem(PrimaryBody::Earth(), {});
  }

  // Information on this orbital system
  std::string info();
};

#endif // ORBITALSYSTEM_H
