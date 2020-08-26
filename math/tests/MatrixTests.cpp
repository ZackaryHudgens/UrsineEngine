#include <catch2/catch.hpp>

#include "Matrix.hpp"

using math::Matrix;

TEST_CASE("Value Accessor")
{
  Matrix a(4, 4);

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
  Matrix a(4, 4);

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
  Matrix a(4, 4), b(4, 4);

  a.SetValue(1, 1, 5);
  b.SetValue(1, 1, 5);

  REQUIRE(a == b);

  a.SetValue(3, 3, 0.009);

  REQUIRE(a != b);
}

TEST_CASE("Identity Matrix")
{
  Matrix a(4, 4), b(4, 4);

  a.SetValue(1, 1, 1);
  a.SetValue(2, 2, 1);
  a.SetValue(3, 3, 1);
  a.SetValue(4, 4, 1);

  b.SetIdentity();

  REQUIRE(a == b);
}

TEST_CASE("Matrix Assignment")
{
  Matrix a(4, 4), b(4, 4);

  a.SetValue(2, 3, 16);
  a.SetValue(4, 2, 9);

  b = a;

  REQUIRE(a == b);
}

TEST_CASE("Matrix Addition")
{
  Matrix a(4, 4), b(4, 4);

  a.SetValue(1, 4, 7);
  a.SetValue(2, 3, 17);
  a.SetValue(3, 4, 2);

  b.SetValue(1, 4, 8);
  b.SetValue(2, 3, 6);
  b.SetValue(3, 1, 7);

  Matrix c(4, 4);

  c.SetValue(1, 4, 15);
  c.SetValue(2, 3, 23);
  c.SetValue(3, 1, 7);
  c.SetValue(3, 4, 2);

  a += b;

  REQUIRE(a == c);
}

TEST_CASE("Matrix Subtraction")
{
  Matrix a(4, 4), b(4, 4);

  a.SetValue(1, 4, 7);
  a.SetValue(2, 3, 17);
  a.SetValue(3, 4, 2);

  b.SetValue(1, 4, 8);
  b.SetValue(2, 3, 6);
  b.SetValue(3, 1, 7);

  Matrix c(4, 4);

  c.SetValue(1, 4, -1);
  c.SetValue(2, 3, 11);
  c.SetValue(3, 1, -7);
  c.SetValue(3, 4, 2);

  a -= b;

  REQUIRE(a == c);
}

TEST_CASE("Matrix Scaling")
{
  Matrix a(4, 4), b(4, 4);

  a.SetValue(1, 2, 4);
  a.SetValue(2, 4, 10);

  b.SetValue(1, 2, 16);
  b.SetValue(2, 4, 40);

  a *= 4;

  REQUIRE(a == b);
}

TEST_CASE("Matrix Multiplication")
{
  Matrix a(2, 3), b(3, 2);

  a.SetValue(1, 3, 5);
  a.SetValue(2, 2, 20);
  a.SetValue(2, 3, 3);

  b.SetValue(1, 2, 2);
  b.SetValue(2, 2, 4);
  b.SetValue(3, 1, 6);

  Matrix c(2, 2);

  c.SetValue(1, 1, 30);
  c.SetValue(2, 1, 18);
  c.SetValue(2, 2, 80);

  a *= b;

  REQUIRE(a == c);
}
