#include "PointLightComponent.hpp"

using UrsineRenderer::PointLightComponent;

PointLightComponent::PointLightComponent()
  : LightComponent()
  , mLinearTerm(0.0)
  , mQuadraticTerm(0.0)
{
}
