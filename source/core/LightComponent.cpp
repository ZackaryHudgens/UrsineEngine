#include "LightComponent.hpp"

#include "Environment.hpp"
#include "ModelComponent.hpp"

using core::LightComponent;

LightComponent::LightComponent()
  : GraphicalComponent()
  , mColor(1.0f, 1.0f, 1.0f)
{
}
