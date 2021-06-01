#include "Vector4D.hpp"

#include <cmath>

#include "Util.hpp"

UrsineMath::Vector4D::Vector4D(double aX,
                               double aY,
                               double aZ,
                               double aW)
{
  mValues.emplace_back(aX);
  mValues.emplace_back(aY);
  mValues.emplace_back(aZ);
  mValues.emplace_back(aW);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator+(double aScalar)
{
  for(auto& value : mValues)
  {
    value += aScalar;
  }

  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator+=(double aScalar)
{
  return (*this + aScalar);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator-(double aScalar)
{
  for(auto& value : mValues)
  {
    value -= aScalar;
  }

  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator-=(double aScalar)
{
  return (*this - aScalar);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator*(double aScalar)
{
  for(auto& value : mValues)
  {
    value *= aScalar;
  }

  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator*=(double aScalar)
{
  return (*this * aScalar);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator/(double aScalar)
{
  for(auto& value : mValues)
  {
    value /= aScalar;
  }

  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator/=(double aScalar)
{
  return (*this / aScalar);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator+(const Vector4D& aVector)
{
  SetX(GetX() + aVector.GetX());
  SetY(GetY() + aVector.GetY());
  SetZ(GetZ() + aVector.GetZ());
  SetW(GetW() + aVector.GetW());
  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator+=(const Vector4D& aVector)
{
  return (*this + aVector);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator-(const Vector4D& aVector)
{
  SetX(GetX() - aVector.GetX());
  SetY(GetY() - aVector.GetY());
  SetZ(GetZ() - aVector.GetZ());
  SetW(GetW() - aVector.GetW());
  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator-=(const Vector4D& aVector)
{
  return (*this - aVector);
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator*(const Matrix4D& aMatrix)
{
  Matrix4D vectorMatrix(1.0);
  vectorMatrix.SetValue(1, 4, GetX()); 
  vectorMatrix.SetValue(2, 4, GetY());
  vectorMatrix.SetValue(3, 4, GetZ());
  vectorMatrix.SetValue(4, 4, GetW());

  Matrix4D result = aMatrix;
  result *= vectorMatrix;

  SetX(result.GetValue(1, 4));
  SetY(result.GetValue(2, 4));
  SetZ(result.GetValue(3, 4));
  SetW(result.GetValue(4, 4));

  return *this;
}

UrsineMath::Vector4D& UrsineMath::Vector4D::operator*=(const Matrix4D& aMatrix)
{
  return (*this * aMatrix);
}

bool UrsineMath::Vector4D::operator==(const Vector4D& aVector) const
{
  return (AlmostEqual(GetX(), aVector.GetX()) &&
          AlmostEqual(GetY(), aVector.GetY()) &&
          AlmostEqual(GetZ(), aVector.GetZ()) &&
          AlmostEqual(GetW(), aVector.GetW()));
}

double UrsineMath::Vector4D::Magnitude() const
{
  return std::sqrt(std::pow(GetX(), 2) +
                   std::pow(GetY(), 2) +
                   std::pow(GetZ(), 2) +
                   std::pow(GetW(), 2));
}

UrsineMath::Vector4D UrsineMath::Vector4D::Normalize() const
{
  Vector4D vec(GetX(), GetY(), GetZ(), GetW());
  vec /= vec.Magnitude();

  return vec;
}

UrsineMath::Vector4D UrsineMath::Vector4D::CrossProduct(const Vector4D& aVector) const
{
  Vector4D vec;

  vec.SetX((GetY() * aVector.GetZ()) - (GetZ() * aVector.GetY()));
  vec.SetY((GetZ() * aVector.GetX()) - (GetX() * aVector.GetZ()));
  vec.SetZ((GetX() * aVector.GetY()) - (GetY() * aVector.GetX()));

  return vec;
}

double UrsineMath::Vector4D::AngleWith(const Vector4D& aVector) const
{
  double product = (GetX() * aVector.GetX() +
                    GetY() * aVector.GetY() +
                    GetZ() * aVector.GetZ() +
                    GetW() * aVector.GetW());

  return std::asin(product);
}
