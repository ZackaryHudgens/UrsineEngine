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
      bool operator==(const Vector3D& aVector) const;
      bool operator!=(const Vector3D& aVector) const;

      Vector3D operator+(const Vector3D& aVector);
      Vector3D operator-(const Vector3D& aVector);
      void operator+=(const Vector3D& aVector);
      void operator-=(const Vector3D& aVector);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Vector3D aVector)
      {
        aStream << "[" << aVector.x() << ", " <<
                aVector.y() << ", " << aVector.z() << "]";
        return aStream;
      }

      /**
       * Returns the x-component of this vector.
       */
      double x() const { return mPoints[0]; }

      /**
       * Returns the y-component of this vector.
       */
      double y() const { return mPoints[1]; }

      /**
       * Returns the z-component of thix vector.
       */
      double z() const { return mPoints[2]; }

      /**
       * Sets the x-component of this vector.
       */
      void x(double aVal) { mPoints[0] = aVal; }

      /**
       * Sets the y-component of this vector.
       */
      void y(double aVal) { mPoints[1] = aVal; }

      /**
       * Sets the z-component of this vector.
       */
      void z(double aVal) { mPoints[2] = aVal; }

      /*
       * Returns the magnitude of this vector.
       */
      double Magnitude() const;

      /**
       * Returns the unit vector for this vector.
       */
      Vector3D Normalize() const;

      /**
       * Returns the angle between this vector and the given vector in degrees.
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

    private:
      double mPoints[3];
  };
}

#endif
