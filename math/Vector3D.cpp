#include "Vector3D.hpp"

#include <cmath>

#include "MathUtils.hpp"

using math::Vector3D;

Vector3D::Vector3D()
{
  mPoints[0] = 0;
  mPoints[1] = 0;
  mPoints[2] = 0;
}

Vector3D::Vector3D(double aX, double aY, double aZ)
{
  mPoints[0] = aX;
  mPoints[1] = aY;
  mPoints[2] = aZ;
}

bool Vector3D::operator==(const Vector3D& aVector) const
{
  return(math::AlmostEqual(mPoints[0], aVector.x()) &&
         math::AlmostEqual(mPoints[1], aVector.y()) &&
         math::AlmostEqual(mPoints[2], aVector.z()));
}

bool Vector3D::operator!=(const Vector3D& aVector) const
{
  return !(*this == aVector);
}

Vector3D Vector3D::operator+(const double& aScalar) const
{
  Vector3D r(x() + aScalar, y() + aScalar, z() + aScalar);
  return r;
}

Vector3D Vector3D::operator-(const double& aScalar) const
{
  Vector3D r(x() - aScalar, y() - aScalar, z() - aScalar);
  return r;
}

Vector3D Vector3D::operator*(const double& aScalar) const
{
  Vector3D r(x() * aScalar, y() * aScalar, z() * aScalar);
  return r;
}

Vector3D Vector3D::operator/(const double& aScalar) const
{
  Vector3D r(x() / aScalar, y() / aScalar, z() / aScalar);
  return r;
}

Vector3D& Vector3D::operator+=(const double& aScalar)
{
  *this = *this + aScalar;
  return *this;
}

Vector3D& Vector3D::operator-=(const double& aScalar)
{
  *this = *this - aScalar;
  return *this;
}

Vector3D& Vector3D::operator*=(const double& aScalar)
{
  *this = *this * aScalar;
  return *this;
}

Vector3D& Vector3D::operator/=(const double& aScalar)
{
  *this = *this / aScalar;
  return *this;
}

Vector3D Vector3D::operator+(const Vector3D& aVector) const
{
  Vector3D r(x() + aVector.x(), y() + aVector.y(), z() + aVector.z());
  return r;
}

Vector3D Vector3D::operator-(const Vector3D& aVector) const
{
  Vector3D r(x() - aVector.x(), y() - aVector.y(), z() - aVector.z());
  return r;
}

Vector3D& Vector3D::operator+=(const Vector3D& aVector)
{
  *this = *this + aVector;
  return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& aVector)
{
  *this = *this - aVector;
  return *this;
}

double Vector3D::Magnitude() const
{
  return sqrt((mPoints[0] * mPoints[0]) +
              (mPoints[1] * mPoints[1]) +
              (mPoints[2] * mPoints[2]));
}

Vector3D Vector3D::Normalize() const
{
  return Vector3D(mPoints[0] / Magnitude(),
                  mPoints[1] / Magnitude(),
                  mPoints[2] / Magnitude());
}

double Vector3D::DotProduct(const Vector3D& aVector) const
{
  Vector3D a = Normalize();
  Vector3D b = aVector.Normalize();

  return (a.x() * b.x()) + (a.y() * b.y()) + (a.z() * b.z());
}

double Vector3D::AngleWith(const Vector3D& aVector) const
{
  return math::RadToDeg(acos(DotProduct(aVector)));
}

bool Vector3D::IsOrthogonalTo(const Vector3D& aVector) const
{
  return math::AlmostEqual(90, AngleWith(aVector));
}

bool Vector3D::IsParallelTo(const Vector3D& aVector) const
{
  return math::AlmostEqual(0, AngleWith(aVector));
}

Vector3D Vector3D::CrossProduct(const Vector3D& aVector) const
{
  return Vector3D((mPoints[1] * aVector.z()) - (mPoints[2] * aVector.y()),
                  (mPoints[2] * aVector.x()) - (mPoints[0] * aVector.z()),
                  (mPoints[0] * aVector.y()) - (mPoints[1] * aVector.x()));
}
