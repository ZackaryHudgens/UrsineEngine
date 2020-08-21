#ifndef VECTOR3D
#define VECTOR3D

#include <iostream>

namespace math
{
  /**
   * A basic 3-dimensional vector with several convenience functions
   * for common vector operations.
   */
  class Vector3D
  {
    public:
      Vector3D();
      Vector3D(double aX, double aY, double aZ);

      void operator=(const Vector3D& aVector);
      bool operator==(const Vector3D& aVector);

      Vector3D operator+(const Vector3D& aVector);
      Vector3D operator-(const Vector3D& aVector);
      void operator+=(const Vector3D& aVector);
      void operator-=(const Vector3D& aVector);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Vector3D aVector)
      {
        aStream << "[" << aVector.x << ", " << aVector.y << aVector.z << "]";
        return aStream;
      }

      /*
       * Returns the magnitude of this vector.
       */
      double Magnitude() const;

      /**
       * Returns the unit vector for this vector.
       */
      Vector3D Normalize() const;

      /**
       * Returns the angle between this vector and the given vector.
       *
       * @param aVector The vector to compare with.
       */
      double AngleWith(const Vector3D& aVector) const;

      /**
       * Returns true if this angle is orthogonal to the given vector.
       *
       * @param aVector The vector to compare with.
       */
      bool IsOrthogonalTo(const Vector3D& aVector) const;

      /**
       * Returns true if this angle is parallel to the given vector.
       *
       * @param aVector The vector to compare with.
       */
      bool IsParallelTo(const Vector3D& aVector) const;

      /**
       * Returns the cross product of this vector and the given vector.
       *
       * @param aVector The vector to compare with.
       */
      Vector3D CrossProduct(const Vector3D& aVector) const;

      double x;
      double y;
      double z;
  };
}

#endif
