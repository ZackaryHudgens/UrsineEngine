#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

namespace math
{
  class Matrix
  {
    public:
      Matrix(int aRowCount, int aColumnCount, bool aIdentity = true);

      void SetValue(int aRow, int aColumn);
      double GetValue(int aRow, int aColumn);

    private:
      std::vector<double> mValues;
  };
}

#endif
