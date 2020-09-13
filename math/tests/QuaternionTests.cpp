#include <catch2/catch.hpp>

#include "Quaternion.hpp"

using math::Quaternion;
using math::Vector3D;

TEST_CASE("Vector3D Rotation")
{
  Quaternion a(90, Vector3D(0.0, 1.0, 0.0));
  Quaternion b(45, Vector3D(1.0, 0.0, 0.0));
  Quaternion c = (b * a);

  Vector3D v(5, 0, 0);

  std::cout << (b * a) * v << std::endl;
  std::cout << c * v << std::endl;
}
