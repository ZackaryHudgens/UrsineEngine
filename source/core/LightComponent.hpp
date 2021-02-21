#ifndef LIGHTCOMPONENT_HPP
#define LIGHTCOMPONENT_HPP

#include "GraphicalComponent.hpp"

namespace core
{
  class LightComponent : public GraphicalComponent
  {
    public:
      LightComponent();

      glm::vec3 GetColor() const { return mColor; }
      void SetColor(const glm::vec3& aColor);

    private:
      glm::vec3 mColor;
  };
}

#endif
