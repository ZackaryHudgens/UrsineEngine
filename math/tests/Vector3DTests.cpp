#include <catch2/catch.hpp>

#include "MathUtils.hpp"
#include "Vector3D.hpp"

using math::Vector3D;

TEST_CASE("Vector3D Equality")
{
  Vector3D a(2, 5, 7.98), b(2, 5, 7.98);

  REQUIRE(a == b);

  b.z(7.97);

  REQUIRE(a != b);
}

TEST_CASE("Vector3D Assignment")
{
  Vector3D a(2, 5, 9.67);
  Vector3D b(0, 0, 0);

  b = a;

  REQUIRE(a == b);
}

TEST_CASE("Vector3D Addition")
{
  Vector3D a(2, 5, 8), b(8, 5, 9);

  a += b;

  Vector3D c(10, 10, 17);

  REQUIRE(a == c);
}

TEST_CASE("Vector3D Subtraction")
{
  Vector3D a(5, 7, 9), b(8, 5, 9);

  a -= b;

  Vector3D c(-3, 2, 0);

  REQUIRE(a == c);
}

TEST_CASE("Vector3D Magnitude")
{
  Vector3D a(4, 5, 8), b(9, 7, 8), c(118.97, 976.39, 82.59);

  REQUIRE(math::AlmostEqual(a.Magnitude(), 10.24695));
  REQUIRE(math::AlmostEqual(b.Magnitude(), 13.92839));
  REQUIRE(math::AlmostEqual(c.Magnitude(), 987.07264));
}

TEST_CASE("Vector3D Normalization")
{
  Vector3D a(55.8, 72.3, 89.28);
  Vector3D b(0.43690, 0.56609, 0.69904);

  REQUIRE(a.Normalize() == b);
}

TEST_CASE("Vector3D Angle Calculation")
{
  Vector3D a(0, 5, 0);
  Vector3D b(0, 0, 5);

  REQUIRE(a.AngleWith(b) == 90);

  Vector3D c(33.6, 72.4, 89.3);
  Vector3D d(89.8, 10.7, 75.2);

  REQUIRE(math::AlmostEqual(c.AngleWith(d), 41.76490));
}

TEST_CASE("Vector3D Orthogonality")
{
  Vector3D a(0, 0, 5);
  Vector3D b(5, 0, 0);

  REQUIRE(a.IsOrthogonalTo(b));

  a.x(96.101);

  REQUIRE(!a.IsOrthogonalTo(b));
}

TEST_CASE("Vector3D Parallelism")
{
  Vector3D a(0, 0, 5);
  Vector3D b(0, 0, 67);

  REQUIRE(a.IsParallelTo(b));

  a.y(-0.001);

  REQUIRE(!a.IsParallelTo(b));
}

TEST_CASE("Vector3D Cross Product")
{
  Vector3D a(54.6, 79.2, 900.3);
  Vector3D b(25.7, 98.1, 107.5);
  Vector3D c(-79805.43, 17268.21, 3320.82);

  REQUIRE(a.CrossProduct(b) == c);
}
