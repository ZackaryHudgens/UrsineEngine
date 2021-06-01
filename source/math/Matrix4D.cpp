#include "Matrix4D.hpp"

#include <iostream>

UrsineMath::Matrix4D::Matrix4D(double aDiagonal)
{
  for(int row = 0; row < 4; ++row)
  {
    for(int column = 0; column < 4; ++column)
    {
      if(row == column)
      {
        mValues.emplace_back(aDiagonal);
      }
      else
      {
        mValues.emplace_back(0.0);
      }
    }
  }
}

UrsineMath::Matrix4D& UrsineMath::Matrix4D::operator*(const Matrix4D& aMatrix)
{
  Matrix4D result(0.0);

  for(int row = 0; row < 4; ++row)
  {
    for(int column2 = 0; column2 < 4; ++column2)
    {
      for(int column = 0; column < 4; ++column)
      {
        double value = result.GetValue(row, column);
        value += GetValue(row, column) * aMatrix.GetValue(column, column2);
        result.SetValue(row, column, value);
      }
    }
  }

  for(int row = 0; row < 4; ++row)
  {
    for(int column = 0; column < 4; ++column)
    {
      SetValue(row, column, result.GetValue(row, column));
    }
  }

  return *this;
}

UrsineMath::Matrix4D& UrsineMath::Matrix4D::operator*=(const Matrix4D& aMatrix)
{
  return (*this * aMatrix);
}

void UrsineMath::Matrix4D::SetValue(int aRow,
                                    int aColumn,
                                    double aValue)
{
  if(aRow < 1 || aRow > 4 || aColumn < 1 || aColumn > 4)
  {
    std::cout << "Arguments for Matrix4D::SetValue are out of range!" << std::endl;
  }
  else
  {
    mValues[(((aRow - 1) * 4) + (aColumn - 1))] = aValue;
  }
}

double UrsineMath::Matrix4D::GetValue(int aRow,
                                      int aColumn) const
{
  double val = 0.0;

  if(aRow < 1 || aRow > 4 || aColumn < 1 || aColumn > 4)
  {
    std::cout << "Arguments for Matrix4D::GetValue are out of range!" << std::endl;
  }
  else
  {
    val = mValues[(((aRow - 1) * 4) + (aColumn - 1))];
  }

  return val;
}
