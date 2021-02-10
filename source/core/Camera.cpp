#include "Camera.hpp"

#include <glm/ext/matrix_transform.hpp>

#include "GameObject.hpp"

using core::Camera;
using core::GameObject;

Camera::Camera()
  : GameObject()
  , mFOV(45.0f)
  , mNearPlane(0.1f)
  , mFarPlane(100.0f)
  , mYaw(0.0)
  , mPitch(0.0)
  , mRoll(0.0)
  , mRightVector(1.0f, 0.0f, 0.0f)
  , mUpVector(0.0f, 1.0f, 0.0f)
  , mFrontVector(0.0f, 0.0f, -1.0f)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
  glm::vec3 position(GetPosition().x, GetPosition().y, GetPosition().z);
  return glm::lookAt(position, position + mFrontVector, mUpVector);
}

void Camera::LookAt(const GameObject& aObject)
{
  LookAt(aObject.GetPosition());
}

void Camera::LookAt(const glm::vec3& aPosition)
{
  mFrontVector = glm::normalize(aPosition);
  UpdateVectors();
}

void Camera::Rotate(double aDegrees, const glm::vec3& aAxis)
{
  // Construct a rotation matrix, then transform our front vector with it.
  glm::vec4 vec(mFrontVector.x, mFrontVector.y, mFrontVector.z, 1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, (float)glm::radians(aDegrees), aAxis);
  vec = trans * vec;

  mFrontVector.x = vec.x;
  mFrontVector.y = vec.y;
  mFrontVector.z = vec.z;

  GameObject::Rotate(aDegrees, aAxis);
  UpdateVectors();
}

void Camera::UpdateVectors()
{
  mRightVector = glm::normalize(glm::cross(mFrontVector, glm::vec3(0.0, 1.0, 0.0)));
  mUpVector = glm::normalize(glm::cross(mRightVector, mFrontVector));
}
