#include "Vector2D.hpp"

#include <cmath>

using math::Vector2D;

const double ALLOWABLE_ERROR = 1e-5;

Vector2D::Vector2D()
  : x(0)
  , y(0)
{
}

Vector2D::Vector2D(double aX, double aY)
  : x(aX)
  , y(aY)
{
}


void Vector2D::operator=(const Vector2D& aVector)
{
  x = aVector.x;
  y = aVector.y;
}

bool Vector2D::operator==(const Vector2D& aVector)
{
  return (fabs(x - aVector.x) < ALLOWABLE_ERROR &&
          fabs(y - aVector.y) < ALLOWABLE_ERROR);
}

Vector2D Vector2D::operator+(const Vector2D& aVector)
{
  x += aVector.x;
  y += aVector.y;
  return *this;
}

Vector2D Vector2D::operator-(const Vector2D& aVector)
{
  x -= aVector.x;
  y -= aVector.y;
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
  return sqrt((x * x) + (y * y));
}

Vector2D Vector2D::Normalize() const
{
  return Vector2D(x / Magnitude(), y / Magnitude());
}

double Vector2D::AngleWith(const Vector2D& aVector) const
{
  Vector2D a = Normalize();
  Vector2D b = aVector.Normalize();

  // As a reminder: this function returns the angle between
  // these two vectors. This is done by taking the arccos of
  // the dot product. The dot product itself is given by summing
  // up the products of each component.
  return acos((a.x * b.x) + (a.y * b.y));
}

bool Vector2D::IsOrthogonalTo(const Vector2D& aVector) const
{
  return fabs(90 - AngleWith(aVector)) < ALLOWABLE_ERROR;
}

bool Vector2D::IsParallelTo(const Vector2D& aVector) const
{
  return fabs(180 - AngleWith(aVector)) < ALLOWABLE_ERROR;
}
