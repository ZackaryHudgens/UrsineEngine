#ifndef VECTOR2D
#define VECTOR2D

#include <iostream>

namespace math
{
  /**
   * A basic 2-dimensional vector with several convenience functions
   * for common vector operations.
   *
   * Note that this is a separate class from Vector3D.
   */
  class Vector2D
  {
    public:
      Vector2D();
      Vector2D(double aX, double aY);

      void operator=(const Vector2D& aVector);
      bool operator==(const Vector2D& aVector);

      Vector2D operator+(const Vector2D& aVector);
      Vector2D operator-(const Vector2D& aVector);
      void operator+=(const Vector2D& aVector);
      void operator-=(const Vector2D& aVector);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Vector2D aVector)
      {
        aStream << "[" << aVector.x << ", " << aVector.y << "]";
        return aStream;
      }

      /*
       * Returns the magnitude of this vector.
       */
      double Magnitude() const;

      /**
       * Returns the unit vector for this vector.
       */
      Vector2D Normalize() const;

      /**
       * Returns the angle between this vector and the given vector.
       *
       * @param aVector The vector to compare with.
       */
      double AngleWith(const Vector2D& aVector) const;

      /**
       * Returns true if this angle is orthogonal to the given vector.
       *
       * @param aVector The vector to compare with.
       */
      bool IsOrthogonalTo(const Vector2D& aVector) const;

      /**
       * Returns true if this angle is parallel to the given vector.
       *
       * @param aVector The vector to compare with.
       */
      bool IsParallelTo(const Vector2D& aVector) const;

      double x;
      double y;
  };
}

#endif
