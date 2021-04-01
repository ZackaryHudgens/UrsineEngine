#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using UrsineRenderer::Camera;

Camera::Camera()
  : GameObject()
  , mForwardVector(0.0, 0.0, -1.0)
  , mUpVector(0.0, 1.0, 0.0)
  , mRightVector(1.0, 0.0, 0.0)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
  return glm::lookAt(GetPosition(),
                     mForwardVector,
                     mUpVector);
}

void Camera::LookAt(const GameObject& aObject)
{
  LookAt(aObject.GetPosition());
}

void Camera::LookAt(const glm::vec3 aPos)
{
  mForwardVector = aPos;
}
