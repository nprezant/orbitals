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

  Vector3 position();
  void setPosition(const Vector3& position);

  Vector3 velocity();
  void setVelocity(const Vector3& velocity);

  ClassicalOrbitalElements orbitalElements();
  void setOrbitalElements(const ClassicalOrbitalElements& orbitalElements);

  double timeSincePerigee();
  void setTimeSincePerigee(double time);

  std::vector<PositionVelocity> orbitalPath(int numPoints);

  double semiMajorAxis();

  double perigeeRadius();

  double apogeeRadius();

  double perigeeVelocity();

  double apogeeVelocity();

  double currentRadius();

  double radialVelocity();

  double azimuthalVelocity();

  double absoluteVelocity();

  double period();

  double flightPathAngle();

  double radiusAtTheta(double theta);

  double azimuthatVelocityAtTheta(double theta);

  double radialVelocityAtTheta(double theta);

  double absoluteVelocityAtTheta(double theta);

  Orbital hohmannTransferTo(Orbital endOrbit);
};

#endif // ORBITAL_H
