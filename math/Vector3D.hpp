#ifndef VECTOR3D
#define VECTOR3D

namespace math
{
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

      Vector3D operator*(const Vector3D& aVector);
      Vector3D operator*(double aFactor);

      double x;
      double y;
      double z;
  };
}

#endif
