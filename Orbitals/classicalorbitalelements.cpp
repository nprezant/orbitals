#include "classicalorbitalelements.h"
#include "matrix3.h"
#include "pi.h"
#include "vector3.h"
#include <cmath>

ClassicalOrbitalElements ClassicalOrbitalElements::fromPositionVelocity(
    const Vector3& position, const Vector3& velocity, double Mu)
{
  // Find orbital elements from the position and velocity vectors
  // given in a geocentric equatorial frame

  // step 1: compute distance
  const double r = position.magnitude();

  // step 2: compute speed
  const double v = velocity.magnitude();

  // step 3: compute radial velocity
  const double radialVelocity = position.dot(velocity / r);

  // step 4: compute specific angular momentum
  const auto hvec = position.cross(velocity);

  // step 5: compute magnitude of h
  const auto h = hvec.magnitude();

  // step 6: compute inclination
  const auto inclination = std::acos(hvec.Z / h);

  // step 7: compute node line vector
  auto Nvec = Vector3(0, 0, 1).cross(hvec);

  // step 7.a: if node line vector is (0,0,0) => it should be (1,0,0) (orbit in
  // equitorial plane)
  if (Nvec == Vector3(0, 0, 0))
  {
    Nvec = Vector3(1, 0, 0);
  }

  // step 8: compute magnitude of node line vector
  const auto N = Nvec.magnitude();

  // step 9: compute RA of the ascending node
  double Omega;
  if (Nvec.Y >= 0)
  {
    Omega = std::acos(Nvec.X / N);
  }
  else
  {
    Omega = 2 * PI - std::acos(Nvec.X / N);
  }

  // step 10: compute eccentricity vector
  const Vector3 factoredPosition = position * (v * v - Mu / r);
  const Vector3 factoredVelocity = velocity * (r * radialVelocity);
  const Vector3 eccentricity = factoredPosition - factoredVelocity * (1 / Mu);

  // step 11: compute eccentricity
  const auto e = eccentricity.magnitude();

  // step 12: compute argument of perigee
  double omega;
  if (eccentricity.Z >= 0)
  {
    omega = std::acos(Nvec.dot(eccentricity) / (N * e));
  }
  else
  {
    omega = 2 * PI - std::acos(Nvec.dot(eccentricity) / (N * e));
  }

  // step 13: compute true anomoly
  double theta;
  if (radialVelocity >= 0)
  {
    theta = std::acos(eccentricity.dot(position) / (e * r));
  }
  else
  {
    theta = 2 * PI - std::acos(eccentricity.dot(position) / (e * r));
  }

  // return the 6 classical orbital elements
  return ClassicalOrbitalElements(theta, h, e, Omega, inclination, omega);
}

PositionVelocity ClassicalOrbitalElements::toPositionVelocity(double Mu) const
{
  // Find position and velocity vectors from orbital elements
  // given in a geocentric equatorial frame

  // step 1: find position vector in perifocal frame
  auto rvecp = Vector3(std::cos(theta), std::sin(theta), 0) *
               (h * h / Mu * 1 / (1 + e * std::cos(theta)));

  // step 2: find velocity vector in perifocal frame
  auto vvecp = Vector3(-std::sin(theta), e + std::cos(theta), 0) * (Mu / h);

  // step 3: compute tansformation matrix
  const auto QXx =
      Matrix3::R3(omega) * Matrix3::R1(inclination) * Matrix3::R3(Omega);
  const auto QxX = QXx.transpose();

  // step 4: transform to geocentric frame
  auto rvec = rvecp * QxX;
  auto vvec = vvecp * QxX;

  // return transformed vectors
  return {rvec, vvec};
}