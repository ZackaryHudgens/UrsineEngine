#include "PyVectorWrapper.hpp"

#include <glm/geometric.hpp>
#include <glm/glm.hpp>

using py::VectorWrapper;

VectorWrapper::VectorWrapper()
  : mVec(0.0, 0.0, 0.0)
{
}

VectorWrapper::VectorWrapper(double aX, double aY, double aZ)
  : mVec(aX, aY, aZ)
{
}

VectorWrapper VectorWrapper::operator+(const VectorWrapper& aVector)
{
  glm::vec3 vec = mVec + aVector.GetVec();
  return VectorWrapper(vec.x, vec.y, vec.z);
}

VectorWrapper VectorWrapper::operator-(const VectorWrapper& aVector)
{
  glm::vec3 vec = mVec - aVector.GetVec();
  return VectorWrapper(vec.x, vec.y, vec.z);
}

VectorWrapper VectorWrapper::Normalize() const
{
  glm::vec3 vec = glm::normalize(mVec);
  return VectorWrapper(vec.x, vec.y, vec.z);
}

VectorWrapper VectorWrapper::CrossProduct(const VectorWrapper& aVector) const
{
  glm::vec3 vec = glm::cross(mVec, aVector.GetVec());
  return VectorWrapper(vec.x, vec.y, vec.z);
}

double VectorWrapper::AngleWith(const VectorWrapper& aVector) const
{
  glm::vec3 a = glm::normalize(mVec);
  glm::vec3 b = glm::normalize(aVector.GetVec());
  double radians = glm::acos(glm::dot(a, b));

  return (radians * 180.0) / M_PI;
}
