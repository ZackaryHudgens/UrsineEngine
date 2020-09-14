#include "MathUtils.hpp"

using math::Matrix4D;
using math::Vector2D;
using math::Vector3D;

const double ALLOWABLE_ERROR = 1e-5;

void math::ScaleMatrix(Matrix4D& aMatrix, const Vector2D& aVector)
{
  Matrix4D m(1);

  m.SetValue(1, 1, aVector.x());
  m.SetValue(2, 2, aVector.y());

  aMatrix *= m;
}

void math::ScaleMatrix(Matrix4D& aMatrix, const Vector3D& aVector)
{
  Matrix4D m(1);

  m.SetValue(1, 1, aVector.x());
  m.SetValue(2, 2, aVector.y());
  m.SetValue(3, 3, aVector.z());

  aMatrix *= m;
}

void math::TranslateMatrix(Matrix4D& aMatrix, const Vector2D& aVector)
{
  Matrix4D m(1);

  m.SetValue(1, 4, aVector.x());
  m.SetValue(2, 4, aVector.y());

  aMatrix *= m;
}

void math::TranslateMatrix(Matrix4D& aMatrix, const Vector3D& aVector)
{
  Matrix4D m(1);

  m.SetValue(1, 4, aVector.x());
  m.SetValue(2, 4, aVector.y());
  m.SetValue(3, 4, aVector.z());

  aMatrix *= m;
}

void RotateMatrix(Matrix4D& aMatrix, const Vector3D& aVector, double aAngle)
{
  Matrix4D m(1);
  Vector3D n = aVector.Normalize();

  m.SetValue(1, 1,
            (cos(aAngle) + (std::pow(n.x(), 2) * (1 - cos(aAngle)))));
  m.SetValue(1, 2,
            (n.x() * n.y() * (1 - cos(aAngle)) - (n.z() * sin(aAngle))));
  m.SetValue(1, 3,
            (n.x() * n.z() * (1 - cos(aAngle)) + (n.y() * sin(aAngle))));
  m.SetValue(2, 1,
            (n.y() * n.x() * (1 - cos(aAngle)) + (n.z() * sin(aAngle))));
  m.SetValue(2, 2,
            (cos(aAngle) + (std::pow(n.y(), 2) * (1 - cos(aAngle)))));
  m.SetValue(2, 3,
            (n.y() * n.z() * (1 - cos(aAngle)) - (n.x() * sin(aAngle))));
  m.SetValue(3, 1,
            (n.z() * n.x() * (1 - cos(aAngle)) - (n.y() * sin(aAngle))));
  m.SetValue(3, 2,
            (n.z() * n.y() * (1 - cos(aAngle)) + (n.x() * sin(aAngle))));
  m.SetValue(3, 3,
            (cos(aAngle) + (std::pow(n.z(), 2) * (1 - cos(aAngle)))));

  aMatrix *= m;
}

bool math::AlmostEqual(double aVal1, double aVal2)
{
  return std::fabs(aVal1 - aVal2) <= ALLOWABLE_ERROR;
}

double math::RadToDeg(double aRadians)
{
  return aRadians * (180.0 / M_PI);
}

double math::DegToRad(double aDegrees)
{
  return aDegrees / (180.0 / M_PI);
}
