#include "orbital.h"

#include "pi.h"

std::vector<PositionVelocity> Orbital::orbitalPath(int numPoints)
{
  // Finds the position and velocity for many points around the orbit

  auto points = std::vector<PositionVelocity>();
  points.reserve(numPoints);

  const double step = 2 * PI / static_cast<double>(numPoints);

  for (double theta = 0; theta < 2 * PI; theta += step)
  {
    // Update theta
    const auto elements = ClassicalOrbitalElements(
        theta, classicalOrbitalElements_.h, classicalOrbitalElements_.e,
        classicalOrbitalElements_.Omega, classicalOrbitalElements_.inclination,
        classicalOrbitalElements_.omega, classicalOrbitalElements_.Mu);

    // Figure out and store position and velocity at this location
    points.emplace_back(elements.positionVelocity());
  }

  return points;
}