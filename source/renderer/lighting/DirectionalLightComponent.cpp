#include "DirectionalLightComponent.hpp"

using UrsineRenderer::DirectionalLightComponent;

DirectionalLightComponent::DirectionalLightComponent()
  : LightComponent()
  , mDirection(0.0, 0.0, 0.0)
{
}

void DirectionalLightComponent::SetDirection(const glm::vec3& aDirection)
{
  mDirection = glm::normalize(aDirection);
}
