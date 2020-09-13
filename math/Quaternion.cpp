#include "Quaternion.hpp"

#include "MathUtils.hpp"

using math::Quaternion;

Quaternion::Quaternion()
  : mAngle(1)
{
}

Quaternion::Quaternion(double aAngle, const Vector3D& aAxis)
{
  mAngle = cos(math::DegToRad(aAngle) / 2);
  mAxis = aAxis * sin(math::DegToRad(aAngle) / 2);
}

Quaternion Quaternion::operator*(const Quaternion& aQuaternion) const
{
  Quaternion r;

  // Calculate the angle for the new quaternion.
  r.w((w() * aQuaternion.w()) - v().DotProduct(aQuaternion.v()));

  // Calculate the axis of rotation for the new quaternion.
  Vector3D rv;
  rv = v() * aQuaternion.w();
  rv += aQuaternion.v() * w();
  rv += v().CrossProduct(aQuaternion.v());

  r.v(rv);

  return r;
}

Quaternion& Quaternion::operator*=(const Quaternion& aQuaternion)
{
  *this = *this * aQuaternion;
  return *this;
}

Vector3D Quaternion::operator*(const Vector3D& aVector) const
{
  Vector3D vc = v().CrossProduct(aVector);
  Vector3D r = aVector + (vc * (2 * w())) + (v().CrossProduct(vc) * 2);

  return r;
}

Quaternion Quaternion::Invert() const
{
  Quaternion r(w(), (v() * -1));
  return r;
}
