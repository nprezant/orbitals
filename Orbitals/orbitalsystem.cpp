#include "orbitalsystem.h"
#include <assert.h>
#include <string>

void OrbitalSystem::addOrbital(const Orbital& orbital)
{
  // Primary body of added orbit must be the same as the system's primary body.
  assert(orbital.primaryBody() == primaryBody_);
  orbitals_.push_back(orbital);
}

void OrbitalSystem::addClassicalOrbitalElementsOrbit(
    const ClassicalOrbitalElements& classicalOrbitalElements)
{
  addOrbital(Orbital::fromClassicalOrbitalElements(
      classicalOrbitalElements, primaryBody_));
}

void OrbitalSystem::addPositionVelocityOrbit(
    const Vector3& position, const Vector3& velocity)
{
  addOrbital(Orbital::fromPositionVelocity(position, velocity, primaryBody_));
}

void OrbitalSystem::addPositionVelocityOrbit(
    const PositionVelocity& positionVelocity)
{
  addOrbital(Orbital::fromPositionVelocity(positionVelocity, primaryBody_));
}

void OrbitalSystem::addEllipticalOrbit(
    double perigeeRadius, double apogeeRadius, double omega)
{
  addOrbital(
      Orbital::elliptical(perigeeRadius, apogeeRadius, omega, primaryBody_));
}

void OrbitalSystem::addCircularOrbitRadius(double radius)
{
  addOrbital(Orbital::circularRadius(radius, primaryBody_));
}

void OrbitalSystem::addCircularOrbitVelocity(double velocity)
{
  addOrbital(Orbital::circularVelocity(velocity, primaryBody_));
}

void OrbitalSystem::addLambertOrbit(
    const Vector3& positionStart, const Vector3& positionEnd, double deltaT)
{
  addOrbital(
      Orbital::fromLambert(positionStart, positionEnd, deltaT, primaryBody_));
}

void OrbitalSystem::incrementTime(double step)
{
  for (auto& orbital : orbitals_)
    orbital.incrementTimeSincePerigee(step);
}

std::string OrbitalSystem::info()
{
  std::string s;

  // Primary body into
  s += "Primary body: " + primaryBody_.name + "\n";

  // System info
  const auto numOrbitals = std::to_string(static_cast<int>(orbitals_.size()));
  s += "num orbitals: " + numOrbitals + "\n";

  // Info for each orbital
  for (const auto& orbital : orbitals_)
    s += orbital.info();

  return s;
}
