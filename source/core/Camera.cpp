#include "Camera.hpp"
#include "GameObject.hpp"
#include <glm/ext/matrix_transform.hpp>

using core::Camera;
using core::GameObject;

Camera::Camera()
  : GameObject()
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

void Camera::LookAt(const glm::vec4& aPosition)
{
  mTarget = glm::vec3(aPosition.x, aPosition.y, aPosition.z);
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
