#include "Matrix.hpp"

#include <iostream>

#include "MathUtils.hpp"

using math::Matrix;
using math::Vector2D;
using math::Vector3D;

Matrix::Matrix(int aRowCount, int aColumnCount)
  : mRows(aRowCount)
  , mColumns(aColumnCount)
{
  for(int i = 0; i < mRows; ++i)
  {
    for(int j = 0; j < mColumns; ++j)
    {
      mValues.emplace_back(0);
    }
  }
}

void Matrix::operator=(const Matrix& aMatrix)
{
  mRows = aMatrix.mRows;
  mColumns = aMatrix.mColumns;
  mValues = aMatrix.mValues;
}

bool Matrix::operator==(const Matrix& aMatrix) const
{
  bool equalValues = true;
  if(mRows == aMatrix.mRows && mColumns == aMatrix.mColumns)
  {
    for(int i = 0; i < mValues.size(); ++i)
    {
      if(!math::AlmostEqual(mValues.at(i), aMatrix.mValues.at(i)))
      {
        equalValues = false;
        break;
      }
    }
  }
  else
  {
    equalValues = false;
  }

  return equalValues;
}

bool Matrix::operator!=(const Matrix& aMatrix) const
{
  return !(*this == aMatrix);
}

Matrix Matrix::operator+(const Matrix& aMatrix)
{
  try
  {
    if(!CanBeAdded(aMatrix))
    {
      throw MatrixOperationException();
    }
  }
  catch(MatrixOperationException& e)
  {
    std::cout << e.what() << std::endl;
  }

  Matrix mat(mRows, mColumns);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = mValues.at(i) + aMatrix.mValues.at(i);
  }

  return mat;
}

Matrix Matrix::operator-(const Matrix& aMatrix)
{
  try
  {
    if(!CanBeAdded(aMatrix))
    {
      throw MatrixOperationException();
    }
  }
  catch(MatrixOperationException& e)
  {
    std::cout << e.what() << std::endl;
  }

  Matrix mat(mRows, mColumns);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = mValues.at(i) - aMatrix.mValues.at(i);
  }

  return mat;
}

Matrix Matrix::operator*(double aScalar)
{
  Matrix mat(mRows, mColumns);
  for(int i = 0; i < mValues.size(); ++i)
  {
    mat.mValues.at(i) = (mValues.at(i) * aScalar);
  }

  return mat;
}

Matrix Matrix::operator*(const Matrix& aMatrix)
{
  try
  {
    if(!CanBeMultiplied(aMatrix))
    {
      throw MatrixOperationException();
    }
  }
  catch(MatrixOperationException& e)
  {
    std::cout << e.what() << std::endl;
  }

  Matrix mat(mRows, aMatrix.mColumns);
  for(int i = 1; i < mRows + 1; ++i)
  {
    for(int j = 1; j < aMatrix.mColumns + 1; ++j)
    {
      double val = mat.GetValue(i, j);
      for(int k = 1; k < mColumns + 1; ++k)
      {
        val += (GetValue(i, k) * aMatrix.GetValue(k, j));
        mat.SetValue(i, j, val);
      }
    }
  }

  return mat;
}

Vector2D Matrix::operator*(const Vector2D& aVector)
{
  // Create an Mx1 matrix from this vector.
  Matrix trans(mRows, 1);
  trans.SetValue(1, 1, aVector.x());
  trans.SetValue(2, 1, aVector.y());

  // Transform the vector in matrix form.
  trans *= *this;

  // Convert the matrix back to a vector, then return it.
  Vector2D vec(trans.GetValue(1, 1), trans.GetValue(2, 1));
  return vec;
}

Vector3D Matrix::operator*(const Vector3D& aVector)
{
  // Create an Mx1 matrix from this vector.
  Matrix trans(mRows, 1);
  trans.SetValue(1, 1, aVector.x());
  trans.SetValue(2, 1, aVector.y());
  trans.SetValue(3, 1, aVector.z());

  // Transform the vector in matrix form.
  trans *= *this;

  // Convert the matrix back to a vector, then return it.
  Vector3D vec(trans.GetValue(1, 1),
               trans.GetValue(2, 1),
               trans.GetValue(3, 1));
  return vec;
}

void Matrix::operator+=(const Matrix& aMatrix)
{
  *this = *this + aMatrix;
}

void Matrix::operator-=(const Matrix& aMatrix)
{
  *this = *this - aMatrix;
}

void Matrix::operator*=(double aScalar)
{
  *this = *this * aScalar;
}

void Matrix::operator*=(const Matrix& aMatrix)
{
  *this = *this * aMatrix;
}

void Matrix::SetIdentity()
{
  for(int i = 0; i < mRows; ++i)
  {
    for(int j = 0; j < mColumns; ++j)
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

void Matrix::SetValue(int aRow, int aColumn, double aValue)
{
  int index = ((aRow - 1) * mColumns) + (aColumn - 1);
  mValues.at(index) = aValue;
}

double Matrix::GetValue(int aRow, int aColumn) const
{
  int index = ((aRow - 1) * mColumns) + (aColumn - 1);
  return mValues.at(index);
}

bool Matrix::CanBeAdded(const Matrix& aMatrix) const
{
  return (aMatrix.mRows == mRows) &&
         (aMatrix.mColumns == mColumns);
}

bool Matrix::CanBeMultiplied(const Matrix& aMatrix) const
{
  return (mColumns == aMatrix.mRows);
}
