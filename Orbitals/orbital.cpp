#include "orbital.h"

#include "lambert.h"
#include "newtonsmethod.h"
#include "pi.h"
#include <cmath>
#include <stdexcept>

Orbital Orbital::fromClassicalOrbitalElements(
    const ClassicalOrbitalElements& classicalOrbitalElements,
    const PrimaryBody& primaryBody)
{
  const auto pv = classicalOrbitalElements.toPositionVelocity(primaryBody.Mu);

  return Orbital(
      primaryBody, pv.position, pv.velocity, classicalOrbitalElements);
}

Orbital Orbital::fromPositionVelocity(
    const Vector3& position,
    const Vector3& velocity,
    const PrimaryBody& primaryBody)
{
  const auto elements = ClassicalOrbitalElements::fromPositionVelocity(
      position, velocity, primaryBody.Mu);

  return Orbital(primaryBody, position, velocity, elements);
}

Orbital Orbital::fromPositionVelocity(
    const PositionVelocity& positionVelocity, const PrimaryBody& primaryBody)
{
  return Orbital::fromPositionVelocity(
      positionVelocity.position, positionVelocity.velocity, primaryBody);
}

Orbital Orbital::elliptical(
    double perigeeRadius,
    double apogeeRadius,
    double omega,
    const PrimaryBody& primaryBody)
{
  auto Mu = primaryBody.Mu;

  double theta = 0;
  double h = std::sqrt(2 * Mu) * std::sqrt(
                                     (apogeeRadius * perigeeRadius) /
                                     (apogeeRadius + perigeeRadius));
  double e = (apogeeRadius - perigeeRadius) / (apogeeRadius + perigeeRadius);
  double Omega = 0;
  double inclination = 0;

  const auto elements =
      ClassicalOrbitalElements(theta, h, e, Omega, inclination, omega);

  return Orbital::fromClassicalOrbitalElements(elements, primaryBody);
}

Orbital Orbital::circularRadius(double radius, const PrimaryBody& primaryBody)
{
  auto Mu = primaryBody.Mu;
  auto v = std::sqrt(Mu / radius);
  auto theta = 0;
  auto h = v * radius;
  auto e = 0;
  auto Omega = 0;
  auto inclination = 0;
  auto omega = 0;

  const auto elements =
      ClassicalOrbitalElements(theta, h, e, Omega, inclination, omega);

  return Orbital::fromClassicalOrbitalElements(elements, primaryBody);
}

Orbital
Orbital::circularVelocity(double velocity, const PrimaryBody& primaryBody)
{
  auto Mu = primaryBody.Mu;
  auto r = Mu / (velocity * velocity);
  auto theta = 0;
  auto h = r * velocity;
  auto e = 0;
  auto Omega = 0;
  auto inclination = 0;
  auto omega = 0;

  const auto elements =
      ClassicalOrbitalElements(theta, h, e, Omega, inclination, omega);

  return Orbital::fromClassicalOrbitalElements(elements, primaryBody);
}

Orbital Orbital::fromLambert(
    const Vector3& positionStart,
    const Vector3& positionEnd,
    double deltaT,
    const PrimaryBody& primaryBody)
{
  // time given in seconds

  const auto startEndPVs =
      Lambert::compute(positionStart, positionEnd, deltaT, primaryBody.Mu);
  const auto& startPV = startEndPVs.startPositionVelocity;

  const auto position = startPV.position;
  const auto velocity = startPV.velocity;

  const auto elements = ClassicalOrbitalElements::fromPositionVelocity(
      position, velocity, primaryBody.Mu);

  return Orbital(primaryBody, position, velocity, elements);
}

Vector3 Orbital::position() { return position_; }

void Orbital::setPosition(const Vector3& position)
{
  const auto elements = ClassicalOrbitalElements::fromPositionVelocity(
      position, velocity_, primaryBody_.Mu);

  position_ = position;
  classicalOrbitalElements_ = elements;
}

Vector3 Orbital::velocity() { return velocity_; }

void Orbital::setVelocity(const Vector3& velocity)
{
  const auto elements = ClassicalOrbitalElements::fromPositionVelocity(
      position_, velocity, primaryBody_.Mu);

  velocity_ = velocity;
  classicalOrbitalElements_ = elements;
}

ClassicalOrbitalElements Orbital::classicalOrbitalElements()
{
  return classicalOrbitalElements_;
}

void Orbital::setClassicalOrbitalElements(
    const ClassicalOrbitalElements& elements)
{
  const auto positionVelocity = elements.toPositionVelocity(primaryBody_.Mu);
  position_ = positionVelocity.position;
  velocity_ = positionVelocity.velocity;
  classicalOrbitalElements_ = elements;
}

PrimaryBody Orbital::primaryBody() { return primaryBody_; }

void Orbital::setPrimaryBody(const PrimaryBody& primaryBody)
{
  const auto positionVelocity =
      classicalOrbitalElements_.toPositionVelocity(primaryBody.Mu);
  position_ = positionVelocity.position;
  velocity_ = positionVelocity.velocity;
  primaryBody_ = primaryBody;
}

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
        classicalOrbitalElements_.omega);

    // Figure out and store position and velocity at this location
    points.emplace_back(elements.toPositionVelocity(primaryBody_.Mu));
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

double Orbital::radius()
{
  return semiMajorAxis() *
         (1 - classicalOrbitalElements_.e * classicalOrbitalElements_.e) /
         (1 + classicalOrbitalElements_.e *
                  std::cos(classicalOrbitalElements_.theta));
}

double Orbital::radius(double theta)
{
  const auto h = classicalOrbitalElements_.h;
  const auto e = classicalOrbitalElements_.e;
  const auto Mu = primaryBody_.Mu;
  return (h * h) / Mu * 1.0 / (1.0 + e * std::cos(theta));
}

double Orbital::radialVelocity()
{
  return radialVelocity(classicalOrbitalElements_.theta);
}

double Orbital::radialVelocity(double theta)
{
  return primaryBody_.Mu / classicalOrbitalElements_.h *
         classicalOrbitalElements_.e * std::sin(theta);
}

double Orbital::azimuthalVelocity()
{
  return classicalOrbitalElements_.h / radius();
}

double Orbital::azimuthalVelocity(double theta)
{
  return classicalOrbitalElements_.h / radius(theta);
}

double Orbital::absoluteVelocity()
{
  auto vRadial = radialVelocity();
  auto vAzimuthal = azimuthalVelocity();
  return std::sqrt(vRadial * vRadial + vAzimuthal * vAzimuthal);
}

double Orbital::absoluteVelocity(double theta)
{
  auto vRadial = radialVelocity(theta);
  auto vAzimuthal = azimuthalVelocity(theta);
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

double Orbital::flightPathAngle(double theta)
{
  return std::atan(radialVelocity(theta) / azimuthalVelocity(theta));
}

Orbital Orbital::hohmannTransferTo(Orbital endOrbit)
{
  // Returns orbital for hohmann transfer ellipse between
  // the two orbits. Both orbits MUST share an apse line.
  auto startTheta = classicalOrbitalElements_.theta;
  auto endTheta = startTheta + PI; // 180 degrees

  auto rStartTransfer = radius(startTheta);
  auto rEndTransfer = endOrbit.radius(endTheta);

  return Orbital::elliptical(
      rStartTransfer, rEndTransfer, startTheta, primaryBody_);
}