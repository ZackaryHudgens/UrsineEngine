#ifndef MATRIX4D_HPP
#define MATRIX4D_HPP

#include <ostream>
#include <vector>

namespace UrsineMath
{
  /**
   * A 4x4 matrix of doubles. By default, this class creates
   * an identity matrix.
   */
  class Matrix4D
  {
    public:
      Matrix4D(double aDiagonal = 1.0);

      Matrix4D& operator*(const Matrix4D& aMatrix);
      Matrix4D& operator*=(const Matrix4D& aMatrix);

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Matrix4D& aMatrix)
      {
        for(int row = 0; row < 4; ++row)
        {
          aStream << "| ";
          for(int column = 0; column < 4; ++column)
          {
            aStream << aMatrix.GetValue(row + 1, column + 1) << " ";
          }
          aStream << "|\n";
        }
        return aStream;
      }

      void SetValue(int aRow, int aColumn, double aValue);
      double GetValue(int aRow, int aColumn) const;

      double* GetData() { return mValues.data(); }

    private:
      std::vector<double> mValues;
  };
}

#endif
