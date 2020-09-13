#include "Vector2D.hpp"

#include <cmath>

#include "MathUtils.hpp"

using math::Vector2D;

Vector2D::Vector2D()
{
  mPoints[0] = 0;
  mPoints[1] = 0;
}

Vector2D::Vector2D(double aX, double aY)
{
  mPoints[0] = aX;
  mPoints[1] = aY;
}

bool Vector2D::operator==(const Vector2D& aVector) const
{
  return(math::AlmostEqual(mPoints[0], aVector.x()) &&
         math::AlmostEqual(mPoints[1], aVector.y()));
}

bool Vector2D::operator!=(const Vector2D& aVector) const
{
  return !(*this == aVector);
}

Vector2D Vector2D::operator+(const double& aScalar) const
{
  Vector2D r(x() + aScalar, y() + aScalar);
  return r;
}

Vector2D Vector2D::operator-(const double& aScalar) const
{
  Vector2D r(x() - aScalar, y() - aScalar);
  return r;
}

Vector2D Vector2D::operator*(const double& aScalar) const
{
  Vector2D r(x() * aScalar, y() * aScalar);
  return r;
}

Vector2D Vector2D::operator/(const double& aScalar) const
{
  Vector2D r(x() / aScalar, y() / aScalar);
  return r;
}

Vector2D& Vector2D::operator+=(const double& aScalar)
{
  *this = *this + aScalar;
  return *this;
}

Vector2D& Vector2D::operator-=(const double& aScalar)
{
  *this = *this - aScalar;
  return *this;
}

Vector2D& Vector2D::operator*=(const double& aScalar)
{
  *this = *this * aScalar;
  return *this;
}

Vector2D& Vector2D::operator/=(const double& aScalar)
{
  *this = *this / aScalar;
  return *this;
}

Vector2D Vector2D::operator+(const Vector2D& aVector) const
{
  Vector2D r(x() + aVector.x(), y() + aVector.y());
  return r;
}

Vector2D Vector2D::operator-(const Vector2D& aVector) const
{
  Vector2D r(x() - aVector.x(), y() - aVector.y());
  return r;
}

Vector2D& Vector2D::operator+=(const Vector2D& aVector)
{
  *this = *this + aVector;
  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& aVector)
{
  *this = *this - aVector;
  return *this;
}

double Vector2D::Magnitude() const
{
  return sqrt((mPoints[0] * mPoints[0]) + (mPoints[1] * mPoints[1]));
}

Vector2D Vector2D::Normalize() const
{
  return Vector2D(mPoints[0] / Magnitude(), mPoints[1] / Magnitude());
}

double Vector2D::DotProduct(const Vector2D& aVector) const
{
  Vector2D a = Normalize();
  Vector2D b = aVector.Normalize();

  return ((a.x() * b.x()) + (a.y() * b.y()));
}

double Vector2D::AngleWith(const Vector2D& aVector) const
{
  return math::RadToDeg(acos(DotProduct(aVector)));
}

bool Vector2D::IsOrthogonalTo(const Vector2D& aVector) const
{
  return math::AlmostEqual(90, AngleWith(aVector));
}

bool Vector2D::IsParallelTo(const Vector2D& aVector) const
{
  return math::AlmostEqual(0, AngleWith(aVector));
}
