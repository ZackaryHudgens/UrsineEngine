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
      bool operator==(const Vector2D& aVector) const;
      bool operator!=(const Vector2D& aVector) const;

      Vector2D operator+(const Vector2D& aVector);
      Vector2D operator-(const Vector2D& aVector);
      void operator+=(const Vector2D& aVector);
      void operator-=(const Vector2D& aVector);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Vector2D aVector)
      {
        aStream << "[" << aVector.x() << ", " << aVector.y() << "]";
        return aStream;
      }

      /**
       * Returns the x-coordinate of this vector.
       */
      double x() const { return mPoints[0]; }

      /**
       * Returns the y-coordinate of this vector.
       */
      double y() const { return mPoints[1]; }

      /**
       * Sets the x-component of this vector.
       */
      void x(double aVal) { mPoints[0] = aVal; }

      /**
       * Sets the y-component of this vector.
       */
      void y(double aVal) { mPoints[1] = aVal; }

      /*
       * Returns the magnitude of this vector.
       */
      double Magnitude() const;

      /**
       * Returns the unit vector for this vector.
       */
      Vector2D Normalize() const;

      /**
       * Returns the angle between this vector and the given vector in degrees.
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

    private:
      double mPoints[2];
  };
}

#endif
