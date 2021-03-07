#include "LightComponent.hpp"

#include "Environment.hpp"
#include "ModelComponent.hpp"

using UrsineRenderer::LightComponent;

LightComponent::LightComponent()
  : Component()
  , mColor(1.0f, 1.0f, 1.0f)
{
}

void LightComponent::SetAmbientIntensity(double aIntensity)
{
  aIntensity = std::max(std::min(aIntensity, 1.0), 0.0);
  mAmbientIntensity = aIntensity;
}

void LightComponent::SetDiffuseIntensity(double aIntensity)
{
  aIntensity = std::max(std::min(aIntensity, 1.0), 0.0);
  mDiffuseIntensity = aIntensity;
}

void LightComponent::SetSpecularIntensity(double aIntensity)
{
  aIntensity = std::max(std::min(aIntensity, 1.0), 0.0);
  mSpecularIntensity = aIntensity;
}
