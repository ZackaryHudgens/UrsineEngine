#include "Util.hpp"

#include <cmath>

bool UrsineMath::AlmostEqual(double a, double b)
{
  return (std::fabs(a - b) < cEPSILON);
}
