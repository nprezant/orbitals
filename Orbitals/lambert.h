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
  struct Result
  {
    PositionVelocity startPositionVelocity;
    PositionVelocity endPositionVelocity;

    Result(
        const PositionVelocity& startPositionVelocity,
        const PositionVelocity& endPositionVelocity)
        : startPositionVelocity(startPositionVelocity),
          endPositionVelocity(endPositionVelocity)
    {
    }
  };

  static Result compute(
      const Vector3& positionStart,
      const Vector3& positionEnd,
      double deltaT,
      double Mu);
};

#endif // LAMBERT_H