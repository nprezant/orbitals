#include "orbital.h"

#include "pi.h"
#include <cmath>

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

double Orbital::semiMajorAxis()
{
  return (classicalOrbitalElements_.h * classicalOrbitalElements_.h) /
         (primaryBody_.Mu *
          (1 - classicalOrbitalElements_.e * classicalOrbitalElements_.e));
}

double Orbital::perigeeRadius()
{
  return semiMajorAxis() * (1 - classicalOrbitalElements_.e);
}

double Orbital::apogeeRadius()
{
  return semiMajorAxis() * (1 + classicalOrbitalElements_.e);
}

double Orbital::perigeeVelocity()
{
  return classicalOrbitalElements_.h / perigeeRadius();
}

double Orbital::apogeeVelocity()
{
  return classicalOrbitalElements_.h / apogeeRadius();
}

double Orbital::currentRadius()
{
  return semiMajorAxis() *
         (1 - classicalOrbitalElements_.e * classicalOrbitalElements_.e) /
         (1 + classicalOrbitalElements_.e *
                  std::cos(classicalOrbitalElements_.theta));
}

double Orbital::radialVelocity()
{
  return primaryBody_.Mu / classicalOrbitalElements_.h *
         classicalOrbitalElements_.e *
         std::sin(classicalOrbitalElements_.theta);
}

double Orbital::azimuthalVelocity()
{
  return classicalOrbitalElements_.h / currentRadius();
}

double Orbital::absoluteVelocity()
{
  auto vRadial = radialVelocity();
  auto vAzimuthal = azimuthalVelocity();
  return std::sqrt(vRadial * vRadial + vAzimuthal * vAzimuthal);
}

double Orbital::period()
{
  return 2 * PI / std::sqrt(primaryBody_.Mu) * std::pow(semiMajorAxis(), 1.5);
}

double Orbital::flightPathAngle()
{
  return std::atan(radialVelocity() / azimuthalVelocity());
}

double Orbital::radiusAtTheta(double theta)
{
  const auto h = classicalOrbitalElements_.h;
  const auto e = classicalOrbitalElements_.e;
  const auto Mu = primaryBody_.Mu;

  return h * h / Mu * 1 / (1 + e * std::cos(theta));
}

double Orbital::azimuthatVelocityAtTheta(double theta)
{
  return primaryBody_.Mu / classicalOrbitalElements_.h *
         (1 + classicalOrbitalElements_.e * std::cos(theta));
}

double Orbital::radialVelocityAtTheta(double theta)
{
  return primaryBody_.Mu / classicalOrbitalElements_.h *
         classicalOrbitalElements_.e * std::sin(theta);
}

double Orbital::absoluteVelocityAtTheta(double theta)
{
  const auto vRad = radialVelocityAtTheta(theta);
  const auto vAzi = azimuthatVelocityAtTheta(theta);

  return std::sqrt(vRad * vRad + vAzi * vAzi);
}