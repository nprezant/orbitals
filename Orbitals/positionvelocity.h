#ifndef POSITIONVELOCITY_H
#define POSITIONVELOCITY_H

#include "vector3.h"

struct PositionVelocity
{
  Vector3 position;
  Vector3 velocity;

  PositionVelocity(const Vector3& position, const Vector3& velocity)
      : position(position), velocity(velocity)
  {
  }
};

#endif // POSITIONVELOCITY_H