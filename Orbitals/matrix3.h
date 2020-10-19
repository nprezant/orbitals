#ifndef MATRIX3_H
#define MATRIX3_H

#include <cmath>

struct Matrix3
{
  double n11;
  double n12;
  double n13;
  double n21;
  double n22;
  double n23;
  double n31;
  double n32;
  double n33;

  inline Matrix3(
      double n11,
      double n12,
      double n13,
      double n21,
      double n22,
      double n23,
      double n31,
      double n32,
      double n33)
      : n11(n11), n12(n12), n13(n13), n21(n21), n22(n22), n23(n23), n31(n31),
        n32(n32), n33(n33)
  {
  }

  // R1 roation matrix
  static Matrix3 R1(double angle)
  {
    return Matrix3(
        1, 0, 0, 0, std::cos(angle), std::sin(angle), 0, -std::sin(angle),
        std::cos(angle));
  }

  // R3 roation matrix
  static Matrix3 R3(double angle)
  {
    return Matrix3(
        std::cos(angle), std::sin(angle), 0, -std::sin(angle), std::cos(angle),
        0, 0, 0, 1);
  }

  inline Matrix3 operator*(const Matrix3& other) const
  {
    auto o11 = other.n11;
    auto o12 = other.n12;
    auto o13 = other.n13;
    auto o21 = other.n21;
    auto o22 = other.n22;
    auto o23 = other.n23;
    auto o31 = other.n31;
    auto o32 = other.n32;
    auto o33 = other.n33;

    auto result0 = n11 * o11 + n12 * o21 + n13 * o31;
    auto result3 = n11 * o12 + n12 * o22 + n13 * o32;
    auto result6 = n11 * o13 + n12 * o23 + n13 * o33;

    auto result1 = n21 * o11 + n22 * o21 + n23 * o31;
    auto result4 = n21 * o12 + n22 * o22 + n23 * o32;
    auto result7 = n21 * o13 + n22 * o23 + n23 * o33;

    auto result2 = n31 * o11 + n32 * o21 + n33 * o31;
    auto result5 = n31 * o12 + n32 * o22 + n33 * o32;
    auto result8 = n31 * o13 + n32 * o23 + n33 * o33;

    return Matrix3(
        result0, result1, result2, result3, result4, result5, result6, result7,
        result8);
  }

  inline Matrix3 transpose() const
  {
    return Matrix3(n11, n21, n31, n12, n22, n32, n13, n23, n33);
  }
};

#endif // MATRIX3_H