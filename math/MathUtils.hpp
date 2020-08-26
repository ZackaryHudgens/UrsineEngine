#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP

#include <cmath>

#include "Matrix.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

namespace math
{
  /**
   * Matrix/Vector Transformation mathods.
   */

  // TODO: CreateTransformationMatrix()
  // should return a transformation matrix that then gets passed
  // to the shader, then used in the shader to multiply the vector
  // instead of applying it to the vector in C++

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
