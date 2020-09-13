#include <catch2/catch.hpp>

#include "Matrix4D.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

using math::Matrix4D;
using math::Vector2D;
using math::Vector3D;

TEST_CASE("Value Accessor")
{
  Matrix4D a(0);

  a.SetIdentity();

  REQUIRE(a.GetValue(1, 1) == 1);
  REQUIRE(a.GetValue(1, 2) == 0);
  REQUIRE(a.GetValue(1, 3) == 0);
  REQUIRE(a.GetValue(1, 4) == 0);
  REQUIRE(a.GetValue(2, 1) == 0);
  REQUIRE(a.GetValue(2, 2) == 1);
  REQUIRE(a.GetValue(2, 3) == 0);
  REQUIRE(a.GetValue(2, 4) == 0);
  REQUIRE(a.GetValue(3, 1) == 0);
  REQUIRE(a.GetValue(3, 2) == 0);
  REQUIRE(a.GetValue(3, 3) == 1);
  REQUIRE(a.GetValue(3, 4) == 0);
  REQUIRE(a.GetValue(4, 1) == 0);
  REQUIRE(a.GetValue(4, 2) == 0);
  REQUIRE(a.GetValue(4, 3) == 0);
  REQUIRE(a.GetValue(4, 4) == 1);
}

TEST_CASE("Value Mutator")
{
  Matrix4D a(0);

  a.SetValue(1, 1, 50);
  a.SetValue(2, 1, 7);
  a.SetValue(3, 4, 18);
  a.SetValue(4, 4, 9);

  REQUIRE(a.GetValue(1, 1) == 50);
  REQUIRE(a.GetValue(2, 1) == 7);
  REQUIRE(a.GetValue(3, 4) == 18);
  REQUIRE(a.GetValue(4, 4) == 9);
}

TEST_CASE("Matrix Equality")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 1, 5);
  b.SetValue(1, 1, 5);

  REQUIRE(a == b);

  a.SetValue(3, 3, 0.009);

  REQUIRE(a != b);
}

TEST_CASE("Identity Matrix")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 1, 1);
  a.SetValue(2, 2, 1);
  a.SetValue(3, 3, 1);
  a.SetValue(4, 4, 1);

  b.SetIdentity();

  REQUIRE(a == b);
}

TEST_CASE("Matrix Assignment")
{
  Matrix4D a(0), b(0);

  a.SetValue(2, 3, 16);
  a.SetValue(4, 2, 9);

  b = a;

  REQUIRE(a == b);
}

TEST_CASE("Matrix Addition")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 4, 7);
  a.SetValue(2, 3, 17);
  a.SetValue(3, 4, 2);

  b.SetValue(1, 4, 8);
  b.SetValue(2, 3, 6);
  b.SetValue(3, 1, 7);

  Matrix4D c(0);

  c.SetValue(1, 4, 15);
  c.SetValue(2, 3, 23);
  c.SetValue(3, 1, 7);
  c.SetValue(3, 4, 2);

  a += b;

  REQUIRE(a == c);
}

TEST_CASE("Matrix Subtraction")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 4, 7);
  a.SetValue(2, 3, 17);
  a.SetValue(3, 4, 2);

  b.SetValue(1, 4, 8);
  b.SetValue(2, 3, 6);
  b.SetValue(3, 1, 7);

  Matrix4D c(0);

  c.SetValue(1, 4, -1);
  c.SetValue(2, 3, 11);
  c.SetValue(3, 1, -7);
  c.SetValue(3, 4, 2);

  a -= b;

  REQUIRE(a == c);
}

TEST_CASE("Matrix Scaling")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 2, 4);
  a.SetValue(2, 4, 10);

  b.SetValue(1, 2, 16);
  b.SetValue(2, 4, 40);

  a *= 4;

  REQUIRE(a == b);
}

TEST_CASE("Matrix Multiplication")
{
  Matrix4D a(0), b(0);

  a.SetValue(1, 3, 5);
  a.SetValue(2, 2, 20);
  a.SetValue(2, 3, 3);

  b.SetValue(1, 2, 2);
  b.SetValue(2, 2, 4);
  b.SetValue(3, 1, 6);

  Matrix4D c(0);

  c.SetValue(1, 1, 30);
  c.SetValue(2, 1, 18);
  c.SetValue(2, 2, 80);

  a *= b;

  REQUIRE(a == c);
}

TEST_CASE("Matrix-Vector Multiplication")
{
  Matrix4D a(0);

  a.SetValue(1, 2, 5);
  a.SetValue(2, 2, 3);
  a.SetValue(3, 4, 7);

  Vector2D b(3, 4), c(20, 12);

  REQUIRE(c == (a * b));

  a.SetValue(3, 3, 7);
  a.SetValue(3, 4, 0);

  Vector3D d(5, 3, 8), e(15, 9, 56);

  REQUIRE(e == (a * d));
}
