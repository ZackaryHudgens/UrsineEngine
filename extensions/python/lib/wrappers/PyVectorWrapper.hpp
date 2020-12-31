#ifndef PYVECTORWRAPPER_HPP
#define PYVECTORWRAPPER_HPP

#include <glm/vec3.hpp>

namespace py
{
  /**
   * A wrapper class for glm::vec4. Created to make math easier when
   * communicating between script and engine.
   */
  class VectorWrapper
  {
    public:
      VectorWrapper();
      VectorWrapper(double aX, double aY, double aZ);

      VectorWrapper operator+(const VectorWrapper& aVector);
      VectorWrapper operator-(const VectorWrapper& aVector);

      VectorWrapper Normalize() const;
      VectorWrapper CrossProduct(const VectorWrapper& aVector) const;

      double AngleWith(const VectorWrapper& aVector) const;

      double x() const { return mVec[0]; }
      double y() const { return mVec[1]; }
      double z() const { return mVec[2]; }

      const glm::vec3& GetVec() const { return mVec; }

    private:
      glm::vec3 mVec;
  };
}

#endif
