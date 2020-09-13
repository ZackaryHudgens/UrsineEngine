#include "Matrix4D.hpp"

#include "MathUtils.hpp"

using math::Matrix4D;
using math::Vector2D;
using math::Vector3D;

Matrix4D::Matrix4D(double aDiagonal)
{
  for(int i = 0; i < 4; ++i)
  {
    for(int j = 0; j < 4; ++j)
    {
      if(i == j)
      {
        mValues.emplace_back(aDiagonal);
      }
      else
      {
        mValues.emplace_back(0);
      }
    }
  }
}

bool Matrix4D::operator==(const Matrix4D& aMatrix) const
{
  return mValues == aMatrix.mValues;
}

bool Matrix4D::operator!=(const Matrix4D& aMatrix) const
{
  return !(*this == aMatrix);
}

Matrix4D Matrix4D::operator*(double aScalar) const
{
  Matrix4D mat(0);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = (mValues.at(i) * aScalar);
  }

  return mat;
}

Matrix4D& Matrix4D::operator*=(double aScalar)
{
  *this = *this * aScalar;
  return *this;
}

Matrix4D Matrix4D::operator+(const Matrix4D& aMatrix) const
{

  Matrix4D mat(0);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = mValues.at(i) + aMatrix.mValues.at(i);
  }

  return mat;
}

Matrix4D Matrix4D::operator-(const Matrix4D& aMatrix) const
{
  Matrix4D mat(0);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = mValues.at(i) - aMatrix.mValues.at(i);
  }

  return mat;
}

Matrix4D Matrix4D::operator*(const Matrix4D& aMatrix) const
{
  Matrix4D mat(0);
  for(int i = 1; i < 5; ++i)
  {
    for(int j = 1; j < 5; ++j)
    {
      double val = mat.GetValue(i, j);
      for(int k = 1; k < 5; ++k)
      {
        val += (GetValue(i, k) * aMatrix.GetValue(k, j));
        mat.SetValue(i, j, val);
      }
    }
  }

  return mat;
}

Vector2D Matrix4D::operator*(const Vector2D& aVector) const
{
  // Create a matrix from this vector.
  Matrix4D mat(0);
  mat.SetValue(1, 1, aVector.x());
  mat.SetValue(2, 1, aVector.y());

  // Transform the vector in matrix form.
  mat = *this * mat;

  // Convert the matrix back to a vector, then return it.
  Vector2D vec(mat.GetValue(1, 1), mat.GetValue(2, 1));
  return vec;
}

Vector3D Matrix4D::operator*(const Vector3D& aVector) const
{
  // Create an matrix from this vector.
  Matrix4D mat(0);
  mat.SetValue(1, 1, aVector.x());
  mat.SetValue(2, 1, aVector.y());
  mat.SetValue(3, 1, aVector.z());

  // Transform the vector in matrix form.
  mat = *this * mat;

  // Convert the matrix back to a vector, then return it.
  Vector3D vec(mat.GetValue(1, 1), mat.GetValue(2, 1), mat.GetValue(3, 1));
  return vec;
}

Matrix4D& Matrix4D::operator+=(const Matrix4D& aMatrix)
{
  *this = *this + aMatrix;
  return *this;
}

Matrix4D& Matrix4D::operator-=(const Matrix4D& aMatrix)
{
  *this = *this - aMatrix;
  return *this;
}

Matrix4D& Matrix4D::operator*=(const Matrix4D& aMatrix)
{
  *this = *this * aMatrix;
  return *this;
}

void Matrix4D::SetIdentity()
{
  for(int i = 0; i < 4; ++i)
  {
    for(int j = 0; j < 4; ++j)
    {
      if(j == i)
      {
        SetValue(i + 1, j + 1, 1);
      }
      else
      {
        SetValue(i + 1, j + 1, 0);
      }
    }
  }
}

void Matrix4D::SetValue(int aRow, int aColumn, double aValue)
{
  int index = ((aRow - 1) * 4) + (aColumn - 1);
  mValues.at(index) = aValue;
}

double Matrix4D::GetValue(int aRow, int aColumn) const
{
  int index = ((aRow - 1) * 4) + (aColumn - 1);
  return mValues.at(index);
}
