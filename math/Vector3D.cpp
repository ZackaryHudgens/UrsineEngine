#include "Vector3D.hpp"

#include <cmath>

using math::Vector3D;

const double ALLOWABLE_ERROR = 1e-5;

Vector3D::Vector3D()
  : x(0)
  , y(0)
  , z(0)
{
}

Vector3D::Vector3D(double aX, double aY, double aZ)
  : x(aX)
  , y(aY)
  , z(aZ)
{
}

void Vector3D::operator=(const Vector3D& aVector)
{
  x = aVector.x;
  y = aVector.y;
  z = aVector.z;
}
