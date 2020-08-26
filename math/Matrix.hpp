#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <exception>
#include <vector>

#include "Vector2D.hpp"
#include "Vector3D.hpp"

namespace math
{
  /**
   * Not all matrices can have every operation performed between them.
   * This exception is raised whenever an operation between two
   * incompatible matrices is attempted.
   */
  class MatrixOperationException : public std::exception
  {
    public:
      const char* what() const noexcept override
      {
        return "This matrix operation cannot be performed!";
      }
  };

  /**
   * A basic n-by-m matrix class with several convenience functions for
   * common matrix operations.
   */
  class Matrix
  {
    public:
      Matrix(int aRowCount, int aColumnCount);

      void operator=(const Matrix& aMatrix);
      bool operator==(const Matrix& aMatrix) const;
      bool operator!=(const Matrix& aMatrix) const;

      Matrix operator+(const Matrix& aMatrix);
      Matrix operator-(const Matrix& aMatrix);
      Matrix operator*(double aScalar);
      Matrix operator*(const Matrix& aMatrix);

      Vector2D operator*(const Vector2D& aVector);
      Vector3D operator*(const Vector3D& aVector);

      void operator+=(const Matrix& aMatrix);
      void operator-=(const Matrix& aMatrix);
      void operator*=(double aScalar);
      void operator*=(const Matrix& aMatrix);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Matrix& aMatrix)
      {
        for(int i = 0; i < aMatrix.GetRows(); ++i)
        {
          for(int j = 0; j < aMatrix.GetColumns(); ++j)
          {
            aStream << aMatrix.GetValue(i + 1, j + 1) << " ";
            if(j != aMatrix.GetColumns() - 1)
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

      /**
       * Returns the number of rows.
       */
      double GetRows() const    { return mRows; }

      /**
       * Returns the number of columns.
       */
      double GetColumns() const { return mColumns; }

    private:
      bool CanBeAdded(const Matrix& aMatrix) const;
      bool CanBeMultiplied(const Matrix& aMatrix) const;

      int mRows, mColumns;
      std::vector<double> mValues;
  };
}

#endif
