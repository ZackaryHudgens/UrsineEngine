#include <catch2/catch.hpp>

#include "MathUtils.hpp"
#include "Vector2D.hpp"

using math::Vector2D;

TEST_CASE("Vector2D Equality")
{
  Vector2D a(2, 5), b(2, 5);

  REQUIRE(a == b);

  a.x(2.001);;

  REQUIRE(a != b);
}

TEST_CASE("Vector2D Assignment")
{
  Vector2D a(2, 5);
  Vector2D b(0, 0);

  a = b;

  REQUIRE(a == b);
}

TEST_CASE("Vector2D Addition")
{
  Vector2D a(2, 5), b(8, 5);

  a += b;

  Vector2D c(10, 10);

  REQUIRE(a == c);
}

TEST_CASE("Vector2D Subtraction")
{
  Vector2D a(5, 7), b(8, 5);

  a -= b;

  Vector2D c(-3, 2);

  REQUIRE(a == c);
}

TEST_CASE("Vector2D Magnitude")
{
  Vector2D a(4, 5), b(9, 7), c(118.97, 976.39);

  REQUIRE(math::AlmostEqual(a.Magnitude(), 6.40312));
  REQUIRE(math::AlmostEqual(b.Magnitude(), 11.40175));
  REQUIRE(math::AlmostEqual(c.Magnitude(), 983.61135));
}

TEST_CASE("Vector2D Normalization")
{
  Vector2D a(55.8, 72.3);
  Vector2D b(0.61098, 0.79165);

  REQUIRE(a.Normalize() == b);
}

TEST_CASE("Vector2D Angle Calculation")
{
  Vector2D a(0, 5);
  Vector2D b(5, 0);

  REQUIRE(a.AngleWith(b) == 90);

  b.x(0);
  b.y(-5);

  REQUIRE(a.AngleWith(b) == 180);

  Vector2D c(33.6, 72.4);
  Vector2D d(89.8, 10.7);

  REQUIRE(math::AlmostEqual(c.AngleWith(d), 58.30957));
}

TEST_CASE("Vector2D Orthogonal Test")
{
  Vector2D a(0, 5);
  Vector2D b(5, 0);

  REQUIRE(a.IsOrthogonalTo(b));

  a.x(96.101);

  REQUIRE(!a.IsOrthogonalTo(b));
}

TEST_CASE("Vector2D Parallel Test")
{
  Vector2D a(5, 0);
  Vector2D b(5, 0);

  REQUIRE(a.IsParallelTo(b));

  a.y(-0.001);

  REQUIRE(!a.IsParallelTo(b));
}
