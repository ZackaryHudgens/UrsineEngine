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
  , mTarget(0.0f, 0.0f, 0.0f)
  , mRightVector(1.0f, 0.0f, 0.0f)
  , mUpVector(0.0f, 1.0f, 0.0f)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
  glm::vec3 position(GetPosition().x, GetPosition().y, GetPosition().z);
  return glm::lookAt(position, mTarget, mUpVector);
}

void Camera::LookAt(const GameObject& aObject)
{
  LookAt(aObject.GetPosition());
}

void Camera::LookAt(const glm::vec3& aPosition)
{
  mTarget = aPosition;
  UpdateVectors();
}

void Camera::Translate(const glm::vec3& aVector)
{
  GameObject::Translate(aVector);
  UpdateVectors();
}

void Camera::Rotate(double aDegrees, const glm::vec3& aAxis)
{
  GameObject::Rotate(aDegrees, aAxis);
  UpdateVectors();
}

void Camera::UpdateVectors()
{
}