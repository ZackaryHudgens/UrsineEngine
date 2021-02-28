#ifndef DIRECTIONALLIGHTCOMPONENT_HPP
#define DIRECTIONALLIGHTCOMPONENT_HPP

#include "LightComponent.hpp"

namespace UrsineRenderer
{
  class DirectionalLightComponent : public LightComponent
  {
    public:
      DirectionalLightComponent();

      glm::vec3 GetDirection() const { return mDirection; }
      void SetDirection(const glm::vec3& aDirection);

    private:
      glm::vec3 mDirection;
  };
}

#endif
