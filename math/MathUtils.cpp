#include "MathUtils.hpp"

using math::Matrix4D;
using math::Vector2D;
using math::Vector3D;

const double ALLOWABLE_ERROR = 1e-5;

void math::ScaleMatrix(Matrix4D& aMatrix, const Vector2D& aVector)
{
  Matrix4D trans(1);

  trans.SetValue(1, 1, aVector.x());
  trans.SetValue(2, 2, aVector.y());

  aMatrix *= trans;
}

void math::ScaleMatrix(Matrix4D& aMatrix, const Vector3D& aVector)
{
  Matrix4D trans(1);

  trans.SetValue(1, 1, aVector.x());
  trans.SetValue(2, 2, aVector.y());
  trans.SetValue(3, 3, aVector.z());

  aMatrix *= trans;
}

void math::TranslateMatrix(Matrix4D& aMatrix, const Vector2D& aVector)
{
  Matrix4D trans(1);

  trans.SetValue(1, 4, aVector.x());
  trans.SetValue(2, 4, aVector.y());

  aMatrix *= trans;
}

void math::TranslateMatrix(Matrix4D& aMatrix, const Vector3D& aVector)
{
  Matrix4D trans(1);

  trans.SetValue(1, 4, aVector.x());
  trans.SetValue(2, 4, aVector.y());
  trans.SetValue(3, 4, aVector.z());

  aMatrix *= trans;
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
