#ifndef MATRIX4D_HPP
#define MATRIX4D_HPP

#include <iostream>
#include <vector>

#include "Vector2D.hpp"
#include "Vector3D.hpp"

namespace math
{
  /**
   * A basic 4x4 matrix class with several convenience functions for
   * common matrix operations.
   */
  class Matrix4D
  {
    public:
      Matrix4D(double aDiagonal);

      // Comparison operators
      bool operator==(const Matrix4D& aMatrix) const;
      bool operator!=(const Matrix4D& aMatrix) const;

      // Scalar multiplication
      Matrix4D operator*(double aScalar) const;

      Matrix4D& operator*=(double aScalar);

      // Vector multiplication
      Vector2D operator*(const Vector2D& aVector) const;
      Vector3D operator*(const Vector3D& aVector) const;

      // Matrix operations
      Matrix4D operator+(const Matrix4D& aMatrix) const;
      Matrix4D operator-(const Matrix4D& aMatrix) const;
      Matrix4D operator*(const Matrix4D& aMatrix) const;

      Matrix4D& operator+=(const Matrix4D& aMatrix);
      Matrix4D& operator-=(const Matrix4D& aMatrix);
      Matrix4D& operator*=(const Matrix4D& aMatrix);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Matrix4D& aMatrix)
      {
        for(int i = 0; i < 4; ++i)
        {
          for(int j = 0; j < 4; ++j)
          {
            aStream << aMatrix.GetValue(i + 1, j + 1) << " ";
            if(j == 3)
            {
              aStream << "\n";
            }
          }
        }

        return aStream;
      }

      /**
       * Sets this matrix to its identity form.
       */
      void SetIdentity();

      /**
       * Sets the value at the given position.
       *
       * @param aRow The row to set.
       * @param aColumn The column to set.
       * @param aValue The value to set the position to.
       */
      void SetValue(int aRow, int aColumn, double aValue);

      /**
       * Returns the value at the given position.
       *
       * @param aRow The row to get.
       * @param aColumn The column to get.
       * @return The value at the given position.
       */
      double GetValue(int aRow, int aColumn) const;

    protected:
      std::vector<double> mValues;
  };
}

#endif
