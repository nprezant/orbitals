#ifndef LAMBERT_H
#define LAMBERT_H

#include "positionvelocity.h"
#include "trajectorytype.h"

class Lambert
{
  static double computeDeltaTheta(
      const Vector3& positionStart,
      const Vector3& positionEnd,
      TrajectoryType trajectorytype);

  static double SFunction(double z);
  static double CFunction(double z);

public:
  static PositionVelocity compute(
      const Vector3& positionStart,
      const Vector3& positionEnd,
      double deltaT,
      double Mu);
};

#endif // LAMBERT_H