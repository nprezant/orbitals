#include "orbital.h"

#include "newtonsmethod.h"
#include "pi.h"
#include <cmath>

double Orbital::timeSincePerigee()
{
  // Find the time since perigee based on the classical orbital elements
  const auto h = classicalOrbitalElements_.h;
  const auto e = classicalOrbitalElements_.e;
  const auto theta = classicalOrbitalElements_.theta;
  const auto Mu = primaryBody_.Mu;

  const auto period =
      2 * PI / (Mu * Mu) * std::pow(h / std::sqrt(1 - e * e), 3);
  const auto E =
      2 * std::atan(std::sqrt((1 - e) / (1 + e)) * std::tan(0.5 * theta));
  const auto time = (E - e * std::sin(E)) * period / (2 * PI);
  return time;
}

void Orbital::setTimeSincePerigee(double time)
{
  // Resets the orbital elements based on the given time since perigee
  const auto h = classicalOrbitalElements_.h;
  const auto e = classicalOrbitalElements_.e;
  const auto Mu = primaryBody_.Mu;

  // find mean anomoly
  auto Me = (Mu * Mu) / (h * h * h) * std::pow(1 - e * e, 1.5) * time;

  // find eccentricic anomoly
  auto Efunc = [e, Me](double E) { return E - e * std::sin(E) - Me; };
  auto Eprimefunc = [e](double E) { return 1 - e * std::cos(E); };

  double guess;
  if (Me <= PI)
  {
    guess = Me + 0.5 * e;
  }
  else
  {
    guess = Me - 0.5 * e;
  }
  const auto E = NewtonsMethod::compute(Efunc, Eprimefunc, guess);

  // define orbital elements for this time
  const auto theta =
      2 * std::atan(std::sqrt((1 + e) / (1 - e)) * std::tan(E / 2));

  classicalOrbitalElements_.theta = theta;
}

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