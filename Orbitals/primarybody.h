#ifndef PRIMARYBODY_H
#define PRIMARYBODY_H

#include "vector3.h"
#include <string>

class PrimaryBody
{
public:
  std::string name;
  Vector3 position;
  double mass;
  double radius;

  PrimaryBody(
      const std::string& name,
      const Vector3& position,
      double mass,
      double radius)
      : name(name), position(position), mass(mass), radius(radius)
  {
  }

  static PrimaryBody Earth()
  {
    double radiusEarth = 6371.0;                  // km
    double massEarth = 5.9722 * std::pow(10, 24); // kg
    return PrimaryBody("Earth", Vector3::origin(), massEarth, radiusEarth);
  }
};

#endif // PRIMARYBODY_H
