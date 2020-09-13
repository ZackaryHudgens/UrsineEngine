#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector3D.hpp"

using math::Vector3D;

namespace math
{
  /**
   * A quaternion class used for performing rotations of vectors in 3D space.
   *
   * Quaternions can be combined via multiplication to perform multiple
   * rotations at once, just like with matrices (which they kind of are?). I
   * could stand to know a lot more about these, but this implementation
   * should suffice for now.
   */
  class Quaternion
  {
    public:
      Quaternion();
      Quaternion(double aAngle, const Vector3D& aAxis);

      // Quaternion operations
      Quaternion operator*(const Quaternion& aQuaternion) const;
      Quaternion& operator*=(const Quaternion& aQuaternion);

      // Vector operations
      Vector3D operator*(const Vector3D& aVector) const;

      // Stream output operator
      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Quaternion& aQuaternion)
      {
        aStream << "(" << aQuaternion.w() << ", " << aQuaternion.v() << ")";
        return aStream;
      }

      /**
       * Returns the w-component (angle) of this quaternion.
       */
      double w() const { return mAngle; }

      /**
       * Returns the v-component (axis of rotation) of this quaternion.
       */
      Vector3D v() const { return mAxis; }

      /**
       * Returns the x-component of the axis of rotation.
       */
      double x() const { return mAxis.x(); }

      /**
       * Returns the y-component of the axis of rotation.
       */
      double y() const { return mAxis.y(); }

      /**
       * Returns the z-component of the axis of rotation.
       */
      double z() const { return mAxis.z(); }

      /**
       * Sets the w-component (angle) of this quaternion.
       */
      void w(double aVal) { mAngle = aVal; }

      /**
       * Sets the v-component (axis of rotation) of this quaternion.
       */
      void v(const Vector3D& aVector) { mAxis = aVector; }

      /**
       * Sets the x-component of the axis of rotation.
       */
      void x(double aVal) { mAxis.x(aVal); }

      /**
       * Sets the y-component of the axis of rotation.
       */
      void y(double aVal) { mAxis.y(aVal); }

      /**
       * Sets the z-component of the axis of rotation.
       */
      void z(double aVal) { mAxis.z(aVal); }

      /**
       * Returns the inverse of this quaternion.
       */
      Quaternion Invert() const;

    private:
      double mAngle;
      Vector3D mAxis;
  };
}

#endif
