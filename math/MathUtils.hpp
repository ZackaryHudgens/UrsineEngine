#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP

#include <cmath>

#include "Matrix4D.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

namespace math
{
  /**
   * Matrix Transformation mathods.
   */

  /**
   * Creates a transformation matrix by applying the given scalar vector.
   *
   * @param aMatrix The transformation matrix.
   * @param aVector The value(s) to scale by for each axis.
   */
  void ScaleMatrix(Matrix4D& aMatrix, const Vector2D& aVector);
  void ScaleMatrix(Matrix4D& aMatrix, const Vector3D& aVector);

  /**
   * Creates a transformation matrix by applying the given translation.
   *
   * @param aMatrix The transformation matrix.
   * @param aVector The translation vector.
   */
  void TranslateMatrix(Matrix4D& aMatrix, const Vector2D& aVector);
  void TranslateMatrix(Matrix4D& aMatrix, const Vector3D& aVector);

  /**
   * Creates a transformation matrix by rotating it by the given angle
   * in degrees around the given axis.
   *
   * @param aMatrix The transformation matrix.
   * @param aVector The axis to rotate around.
   * @param aAngle The amount to rotate in degrees.
   */
  void RotateMatrix(Matrix4D& aMatrix, const Vector2D& aVector, double aAngle);
  void RotateMatrix(Matrix4D& aMatrix, const Vector3D& aVector, double aAngle);

  // TODO: Quaternions?

  /**
   * Conversion methods.
   */

  /**
   * Converts radians to degrees.
   *
   * @param aRadians The value in radians.
   * @return Returns the given value in degrees.
   */
  double RadToDeg(double aRadians);

  /**
   * Converts degrees to radians.
   *
   * @param aDegrees The value in degrees.
   * @return Returns the given value in radians.
   */
  double DegToRad(double aDegrees);

  /**
   * Miscellaneous methods.
   */

  /**
   * Returns true if the two given values are within .00001 of each other.
   *
   * @param aVal1 The first value to compare.
   * @param aVal2 The second value to compare.
   * @return Returns true if the two given values are "equal."
   */
  bool AlmostEqual(double aVal1, double aVal2);
}

#endif
