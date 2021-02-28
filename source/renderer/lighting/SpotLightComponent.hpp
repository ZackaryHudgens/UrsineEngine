#ifndef SPOTLIGHTCOMPONENT_HPP
#define SPOTLIGHTCOMPONENT_HPP

#include "LightComponent.hpp"

namespace UrsineRenderer
{
  class SpotLightComponent : public LightComponent
  {
    public:
      SpotLightComponent();

      glm::vec3 GetDirection() const { return mDirection; }
      void SetDirection(const glm::vec3& aDirection);

      double GetInnerAngle() const      { return mInnerAngle; }
      void SetInnerAngle(double aAngle) { mInnerAngle = aAngle; }

      double GetOuterAngle() const      { return mOuterAngle; }
      void SetOuterAngle(double aAngle) { mOuterAngle = aAngle; }

    private:
      glm::vec3 mDirection;

      double mInnerAngle;
      double mOuterAngle;
  };
}

#endif
