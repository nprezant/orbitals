#ifndef CLASSICALORBITALELEMENTS_H
#define CLASSICALORBITALELEMENTS_H

#include "positionvelocity.h"
#include "vector3.h"

struct ClassicalOrbitalElements
{
  double theta;
  double h;
  double e;
  double Omega;
  double inclination;
  double omega;

  ClassicalOrbitalElements(
      double theta,
      double h,
      double e,
      double Omega,
      double inclination,
      double omega)
      : theta(theta), h(h), e(e), Omega(Omega), inclination(inclination),
        omega(omega)
  {
  }

  static ClassicalOrbitalElements fromPositionVelocity(
      const Vector3& position, const Vector3& velocity, double Mu);

  PositionVelocity toPositionVelocity(double Mu) const;
};

#endif // CLASSICALORBITALELEMENTS_H