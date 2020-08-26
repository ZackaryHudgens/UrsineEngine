#include "MathUtils.hpp"

const double ALLOWABLE_ERROR = 1e-5;

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
