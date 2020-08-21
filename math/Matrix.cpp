#include "Matrix.hpp"

#include <iostream>

using math::Matrix;

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
  return (mRows == aMatrix.mRows) &&
         (mColumns == aMatrix.mColumns) &&
         (mValues == aMatrix.mValues);
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
