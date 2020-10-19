#ifndef ORBITAL_H
#define ORBITAL_H

#include "classicalorbitalelements.h"
#include "positionvelocity.h"
#include "primarybody.h"
#include "vector3.h"
#include <string>
#include <vector>

class Orbital
{
  PrimaryBody primaryBody_;
  Vector3 position_;
  Vector3 velocity_;
  ClassicalOrbitalElements classicalOrbitalElements_;

public:
  Orbital(
      const PrimaryBody& primaryBody,
      const Vector3& position,
      const Vector3& velocity,
      const ClassicalOrbitalElements& classicalOrbitalElements)
      : primaryBody_(primaryBody), position_(position), velocity_(velocity),
        classicalOrbitalElements_(classicalOrbitalElements)
  {
  }

  Vector3 position();
  void setPosition(const Vector3 position);

  Vector3 velocity();
  void setVelocity(const Vector3 velocity);

  ClassicalOrbitalElements orbitalElements();
  void setOrbitalElements(const ClassicalOrbitalElements orbitalElements);

  double time();
  void setTime(double time);

  std::vector<PositionVelocity> orbitalPath(int numPoints);
};

#endif // ORBITAL_H
