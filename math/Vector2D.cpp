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


void Vector2D::operator=(const Vector2D& aVector)
{
  mPoints[0] = aVector.x();
  mPoints[1] = aVector.y();
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

Vector2D Vector2D::operator+(const Vector2D& aVector)
{
  mPoints[0] += aVector.x();
  mPoints[1] += aVector.y();
  return *this;
}

Vector2D Vector2D::operator-(const Vector2D& aVector)
{
  mPoints[0] -= aVector.x();
  mPoints[1] -= aVector.y();
  return *this;
}

void Vector2D::operator+=(const Vector2D& aVector)
{
  *this = *this + aVector;
}

void Vector2D::operator-=(const Vector2D& aVector)
{
  *this = *this - aVector;
}

double Vector2D::Magnitude() const
{
  return sqrt((mPoints[0] * mPoints[0]) + (mPoints[1] * mPoints[1]));
}

Vector2D Vector2D::Normalize() const
{
  return Vector2D(mPoints[0] / Magnitude(), mPoints[1] / Magnitude());
}

double Vector2D::AngleWith(const Vector2D& aVector) const
{
  Vector2D a = Normalize();
  Vector2D b = aVector.Normalize();

  // As a reminder: this function returns the angle between
  // these two vectors. This is done by taking the arccos of
  // the dot product. The dot product itself is given by summing
  // up the products of each component.
  return math::RadToDeg(acos((a.x() * b.x()) + (a.y() * b.y())));
}

bool Vector2D::IsOrthogonalTo(const Vector2D& aVector) const
{
  return math::AlmostEqual(90, AngleWith(aVector));
}

bool Vector2D::IsParallelTo(const Vector2D& aVector) const
{
  return math::AlmostEqual(0, AngleWith(aVector));
}
