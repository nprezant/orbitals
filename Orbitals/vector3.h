#ifndef VECTOR3_H
#define VECTOR3_H

#include "matrix3.h"
#include <cmath>

struct Vector3
{
  double X, Y, Z;

  inline Vector3(const double x, const double y, const double z)
      : X(x), Y(y), Z(z)
  {
  }

  static inline Vector3 origin() { return Vector3(0.0, 0.0, 0.0); }

  inline Vector3 operator+(const Vector3& other) const
  {
    return Vector3(X + other.X, Y + other.Y, Z + other.Z);
  }

  inline Vector3 operator+(const double other) const
  {
    return Vector3(X + other, Y + other, Z + other);
  }

  inline Vector3 operator-(const Vector3& other) const
  {
    return Vector3(X - other.X, Y - other.Y, Z - other.Z);
  }

  inline Vector3 operator-(const double other) const
  {
    return Vector3(X - other, Y - other, Z - other);
  }

  inline Vector3 operator/(const double other) const
  {
    return Vector3(X / other, Y / other, Z / other);
  }

  inline Vector3 operator*(const double other) const
  {
    return Vector3(X * other, Y * other, Z * other);
  }

  inline Vector3 operator*(const Matrix3& m) const
  {
    double x = m.n11 * X + m.n21 * Y + m.n31 * Z;
    double y = m.n12 * X + m.n22 * Y + m.n32 * Z;
    double z = m.n13 * X + m.n23 * Y + m.n33 * Z;

    return Vector3(x, y, z);
  }

  inline bool operator==(const Vector3& other) const
  {
    return X == other.X && Y == other.Y && Z == other.Z;
  }

  inline double dot(const Vector3& other) const
  {
    return other.X * X + other.Y * Y + other.Z * Z;
  }

  inline Vector3 cross(const Vector3& other) const
  {
    auto x = Y * other.Z - other.Y * Z;
    auto y = other.X * Z - X * other.Z;
    auto z = X * other.Y - other.X * Y;
    return Vector3(x, y, z);
  }

  inline double magnitude() const { return std::sqrt(this->dot(*this)); }
};

#endif // VECTOR3_H