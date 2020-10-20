#include "lambert.h"

#include "newtonsmethod.h"
#include "pi.h"
#include <stdexcept>

double Lambert::computeDeltaTheta(
    const Vector3& positionStart,
    const Vector3& positionEnd,
    TrajectoryType trajectoryType)
{
  auto pos1 = positionStart.magnitude();
  auto pos2 = positionEnd.magnitude();

  auto dot = positionStart.dot(positionEnd);
  auto cross = positionStart.cross(positionEnd);
  auto angle = std::acos(dot / (pos1 * pos2));

  double dTheta;
  if (trajectoryType == TrajectoryType::PROGRADE)
  {
    if (cross.Z >= 0)
      dTheta = angle;
    else
      dTheta = 2 * PI - angle;
  }
  else if (trajectoryType == TrajectoryType::RETROGRADE)
  {
    if (cross.Z < 0)
      dTheta = angle;
    else
      dTheta = 2 * PI - angle;
  }
  else
  {
    throw std::runtime_error("Invalid Trajectory Type");
  }

  return dTheta;
}

double Lambert::SFunction(double z)
{
  if (z > 0)
    return (std::sqrt(z) - std::sin(std::sqrt(z))) / std::pow(std::sqrt(z), 3);
  else if (z < 0)
    return (std::sinh(std::sqrt(-z)) - std::sqrt(-z)) /
           std::pow(std::sqrt(-z), 3);
  else
    return 1.0 / 6.0;
}

double Lambert::CFunction(double z)
{
  if (z > 0)
    return (1 - std::cos(std::sqrt(z))) / z;
  else if (z < 0)
    return (std::cosh(std::sqrt(-z)) - 1) / (-z);
  else
    return 0.5;
}

PositionVelocity Lambert::compute(
    const Vector3& positionStart,
    const Vector3& positionEnd,
    double deltaT,
    double Mu)
{
  // step 1: magnitude of position vectors
  const auto r1 = positionStart.magnitude();
  const auto r2 = positionEnd.magnitude();

  // step 2: delta theta (choose prograde/retrograde)
  const auto dTheta =
      computeDeltaTheta(positionStart, positionEnd, TrajectoryType::PROGRADE);

  // step 3: A from 8-22
  const auto A = std::sin(dTheta) * std::sqrt(r1 * r2 / (1 - std::cos(dTheta)));

  // step 4: solve 8-23 for z using Newton's method
  auto gamma = [](double r1, double r2, double z, double A) {
    return r1 + r2 + A * (z * SFunction(z) - 1) / (std::sqrt(CFunction(z)));
  };

  auto gamma0 = gamma(r1, r2, 0, A);

  auto Ffunc = [r1, r2, Mu, deltaT, A, gamma](double z) {
    auto gammaZ = gamma(r1, r2, z, A);
    auto power = std::pow(std::abs(gammaZ / CFunction(z)), 1.5);

    return power * SFunction(z) + A * std::sqrt(gammaZ) -
           std::sqrt(Mu) * deltaT;
  };

  auto Fprimefunc = [r1, r2, A, gamma, gamma0](double z) {
    if (z == 0)
    {
      auto term1 = std::pow(std::sqrt(2) / 40.0 * gamma0, 1.5);
      auto term2 =
          A / 8.0 * (std::sqrt(gamma0) + A * std::sqrt(1 / (2 * gamma0)));
      return term1 + term2;
    }
    else
    {
      auto gammaZ = gamma(r1, r2, z, A);
      auto term1 =
          1.0 / (2.0 * z) * (CFunction(z) - 1.5 * SFunction(z) / CFunction(z)) +
          0.75 * std::pow(SFunction(z), 2) / CFunction(z);

      auto term2 = 3 * SFunction(z) / CFunction(z) * std::sqrt(gammaZ) +
                   A * std::sqrt(CFunction(z) / gammaZ);

      return (std::pow(gammaZ / CFunction(z), 1.5) * term1) + (A / 8.0 * term2);
    }
  };

  auto guess = 0;
  auto z = NewtonsMethod::compute(Ffunc, Fprimefunc, guess);

  // step 4.a: if the sign of z is off, we must have chosen the wrong trajectory
  // TODO this...

  // step 5: compute gamma
  auto gammaZ = gamma(r1, r2, z, A);

  // step 6: compute lagrange coeffs with 8-25
  auto f = 1 - gammaZ / r1;
  auto g = A * std::sqrt(gammaZ / Mu);
  auto fdot = std::sqrt(Mu) / (r1 * r2) * std::sqrt(gammaZ / CFunction(z)) *
              (z * SFunction(z) - 1);
  auto gdot = 1 - gammaZ / r2;

  // step 7: compute velocities at 1 and 2 with 8-17 and 8-18
  auto velocityStart = (positionEnd - positionStart * f) * (1 / g);
  auto velocityEnd = (positionEnd * gdot - positionStart) * (1 / g);

  // step 8: compute classical orbital elements from position and velocity
  return PositionVelocity(positionStart, velocityStart);
}
