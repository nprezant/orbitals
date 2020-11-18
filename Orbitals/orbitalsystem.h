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
  void addOrbital(const Orbital& orbital);

  // Remove a specific orbital from the system
  void removeOrbital(int index);

  // Create and add new orbits to the system
  void addClassicalOrbitalElementsOrbit(const ClassicalOrbitalElements& classicalOrbitalElements);
  void addPositionVelocityOrbit(const Vector3& position, const Vector3& velocity);
  void addPositionVelocityOrbit(const PositionVelocity& positionVelocity);
  void addEllipticalOrbit(double perigeeRadius, double apogeeRadius, double omega);
  void addCircularOrbitRadius(double radius);
  void addCircularOrbitVelocity(double velocity);
  void addLambertOrbit(const Vector3& positionStart, const Vector3& positionEnd, double deltaT);

  // Increment time for entire system
  void incrementTime(double step);

  // Information on this orbital system
  std::string info();

  // Allow range based looping over the orbitals in the system.
  // Only const iterator provided to prevent external code from modifying orbital properties directly.
  std::vector<Orbital>::const_iterator begin() const { return orbitals_.begin(); }
  std::vector<Orbital>::const_iterator end() const { return orbitals_.end(); }

  // Allow indexing access to orbitals
  Orbital operator[](const int index)
  {
    return orbitals_[index];
  }

  // Number of orbitals
  std::size_t size()
  {
    return orbitals_.size();
  }
};

#endif // ORBITALSYSTEM_H
