#ifndef VECTOR4D_HPP
#define VECTOR4D_HPP

#include <ostream>
#include <vector>

#include "Matrix4D.hpp"

namespace UrsineMath
{
  /**
   * A 4-dimensional vector of doubles. The x, y, and z coordinates
   * default to 0, and the w component defaults to 1.
   */
  class Vector4D
  {
    public:
      Vector4D(double aX = 0.0,
               double aY = 0.0,
               double aZ = 0.0,
               double aW = 1.0);

      Vector4D& operator+(double aScalar);
      Vector4D& operator+=(double aScalar);
      Vector4D& operator-(double aScalar);
      Vector4D& operator-=(double aScalar);
      Vector4D& operator*(double aScalar);
      Vector4D& operator*=(double aScalar);
      Vector4D& operator/(double aScalar);
      Vector4D& operator/=(double aScalar);

      Vector4D& operator+(const Vector4D& aVector);
      Vector4D& operator+=(const Vector4D& aVector);
      Vector4D& operator-(const Vector4D& aVector);
      Vector4D& operator-=(const Vector4D& aVector);

      Vector4D& operator*(const Matrix4D& aMatrix);
      Vector4D& operator*=(const Matrix4D& aMatrix);

      bool operator==(const Vector4D& aVector) const;

      friend std::ostream& operator<<(std::ostream& aStream,
                                      const Vector4D& aVector)
      {
        aStream << "[" << aVector.GetX() << ", ";
        aStream << aVector.GetY() << ", ";
        aStream << aVector.GetZ() << ", ";
        aStream << aVector.GetW() << "]";
        return aStream;
      }

      double GetX() const { return mValues[0]; }
      double GetY() const { return mValues[1]; }
      double GetZ() const { return mValues[2]; }
      double GetW() const { return mValues[3]; }

      void SetX(double aX) { mValues[0] = aX; }
      void SetY(double aY) { mValues[1] = aY; }
      void SetZ(double aZ) { mValues[2] = aZ; }
      void SetW(double aW) { mValues[3] = aW; }

      double Magnitude() const;
      Vector4D Normalize() const;
      Vector4D CrossProduct(const Vector4D& aVector) const;
      double AngleWith(const Vector4D& aVector) const;

      double* GetData() { return mValues.data(); }

    private:
      std::vector<double> mValues;
  };
}

#endif
