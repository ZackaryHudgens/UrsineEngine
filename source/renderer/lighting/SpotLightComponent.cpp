#include "SpotLightComponent.hpp"

using UrsineRenderer::SpotLightComponent;

SpotLightComponent::SpotLightComponent()
  : LightComponent()
  , mDirection(0.0, 0.0, 0.0)
  , mInnerAngle(0.0)
  , mOuterAngle(0.0)
{
}

void SpotLightComponent::SetDirection(const glm::vec3& aDirection)
{
  mDirection = glm::normalize(aDirection);
}
