#ifndef ORBITAL_H
#define ORBITAL_H

#include "classicalorbitalelements.h"
#include "positionvelocity.h"
#include "primarybody.h"
#include "vector3.h"
#include <string>
#include <vector>

class Orbital
{
  PrimaryBody primaryBody_;
  Vector3 position_;
  Vector3 velocity_;
  ClassicalOrbitalElements classicalOrbitalElements_;

  Orbital(
      const PrimaryBody& primaryBody,
      const Vector3& position,
      const Vector3& velocity,
      const ClassicalOrbitalElements& classicalOrbitalElements)
      : primaryBody_(primaryBody), position_(position), velocity_(velocity),
        classicalOrbitalElements_(classicalOrbitalElements)
  {
  }

public:
  static Orbital fromClassicalOrbitalElements(
      const ClassicalOrbitalElements& classicalOrbitalElements,
      const PrimaryBody& primaryBody);

  static Orbital fromPositionVelocity(
      const Vector3& position,
      const Vector3& velocity,
      const PrimaryBody& primaryBody);

  static Orbital fromPositionVelocity(
      const PositionVelocity& positionVelocity, const PrimaryBody& primaryBody);

  static Orbital elliptical(
      double perigeeRadius,
      double apogeeRadius,
      double omega,
      const PrimaryBody& primaryBody);

  static Orbital circularRadius(double radius, const PrimaryBody& primaryBody);

  static Orbital
  circularVelocity(double velocity, const PrimaryBody& primaryBody);

  static Orbital fromLambert(
      const Vector3& positionStart,
      const Vector3& positionEnd,
      double deltaT,
      const PrimaryBody& primaryBody);

  Vector3 position() const;
  void setPosition(const Vector3& position);

  Vector3 velocity() const;
  void setVelocity(const Vector3& velocity);

  ClassicalOrbitalElements classicalOrbitalElements() const;
  void setClassicalOrbitalElements(const ClassicalOrbitalElements& elements);

  PrimaryBody primaryBody() const;
  void setPrimaryBody(const PrimaryBody& primaryBody);

  double timeSincePerigee() const;
  void setTimeSincePerigee(double time);

  std::vector<PositionVelocity> orbitalPath(int numPoints) const;

  double semiMajorAxis() const;

  double perigeeRadius() const;

  double apogeeRadius() const;

  double perigeeVelocity() const;

  double apogeeVelocity() const;

  double radius() const;
  double radius(double theta) const;

  double radialVelocity() const;
  double radialVelocity(double theta) const;

  double azimuthalVelocity() const;
  double azimuthalVelocity(double theta) const;

  double absoluteVelocity() const;
  double absoluteVelocity(double theta) const;

  double period() const;

  double flightPathAngle() const;
  double flightPathAngle(double theta) const;

  Orbital hohmannTransferTo(const Orbital& endOrbit) const;
};

#endif // ORBITAL_H
