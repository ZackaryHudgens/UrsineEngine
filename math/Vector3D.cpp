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

bool Vector3D::operator==(const Vector3D& aVector)
{
  return (fabs(x - aVector.x) < ALLOWABLE_ERROR &&
          fabs(y - aVector.y) < ALLOWABLE_ERROR &&
          fabs(z - aVector.z) < ALLOWABLE_ERROR);
}

Vector3D Vector3D::operator+(const Vector3D& aVector)
{
  x += aVector.x;
  y += aVector.y;
  z += aVector.z;
  return *this;
}

Vector3D Vector3D::operator-(const Vector3D& aVector)
{
  x -= aVector.x;
  y -= aVector.y;
  z -= aVector.z;
  return *this;
}

void Vector3D::operator+=(const Vector3D& aVector)
{
  *this = *this + aVector;
}

void Vector3D::operator-=(const Vector3D& aVector)
{
  *this = *this - aVector;
}

double Vector3D::Magnitude() const
{
  return sqrt((x * x) + (y * y) + (z * z));
}

Vector3D Vector3D::Normalize() const
{
  return Vector3D(x / Magnitude(), y / Magnitude(), z / Magnitude());
}

double Vector3D::AngleWith(const Vector3D& aVector) const
{
  Vector3D a = Normalize();
  Vector3D b = aVector.Normalize();

  // As a reminder: this function returns the angle between
  // these two vectors. This is done by taking the arccos of
  // the dot product. The dot product itself is given by summing
  // up the products of each component.
  return acos((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

bool Vector3D::IsOrthogonalTo(const Vector3D& aVector) const
{
  return fabs(90 - AngleWith(aVector)) < ALLOWABLE_ERROR;
}

bool Vector3D::IsParallelTo(const Vector3D& aVector) const
{
  return fabs(180 - AngleWith(aVector)) < ALLOWABLE_ERROR;
}

Vector3D Vector3D::CrossProduct(const Vector3D& aVector) const
{
  return Vector3D((y * aVector.z) - (z * aVector.y),
                  (z * aVector.x) - (x * aVector.z),
                  (x * aVector.y) - (y * aVector.x));
}
