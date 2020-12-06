#include "Camera.hpp"
#include "GameObject.hpp"
#include <glm/ext/matrix_transform.hpp>

using core::Camera;

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
}

void Camera::LookAt(const glm::vec4& aPosition)
{
}
