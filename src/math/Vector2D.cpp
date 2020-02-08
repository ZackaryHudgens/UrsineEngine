#include "Vector2D.hpp"

#include <cmath>

using gMath::Vector2D;

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
  x += aVector.x;
  y += aVector.y;
}

void Vector2D::operator-=(const Vector2D& aVector)
{
  x -= aVector.x;
  y -= aVector.y;
}

Vector2D Vector2D::operator*(const Vector2D& aVector)
{
  x *= aVector.x;
  y *= aVector.y;
  return *this;
}

Vector2D Vector2D::operator*(double aFactor)
{
  x *= aFactor;
  y *= aFactor;
  return *this;
}
