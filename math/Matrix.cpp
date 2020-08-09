#include "Matrix.hpp"

#include <iostream>

using math::Matrix;

Matrix::Matrix(int aRowCount, int aColumnCount, bool aIdentity)
{
  for(int i = 0; i < aRowCount; ++i)
  {
    for(int j = 0; j < aColumnCount; ++j)
    {
      if(aIdentity && j == i)
      {
        mValues.emplace_back(1);
      }
      else
      {
        mValues.emplace_back(0);
      }
    }
  }
}
