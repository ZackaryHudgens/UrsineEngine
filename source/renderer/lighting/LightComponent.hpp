#ifndef LIGHTCOMPONENT_HPP
#define LIGHTCOMPONENT_HPP

#include <glm/glm.hpp>

#include "core/Component.hpp"

using UrsineCore::Component;

namespace UrsineRenderer
{
  class LightComponent : public Component
  {
    public:
      LightComponent();

      glm::vec3 GetColor() const { return mColor; }
      void SetColor(const glm::vec3& aColor);

      double GetAmbientIntensity() const { return mAmbientIntensity; }
      void SetAmbientIntensity(double aIntensity);
      double GetDiffuseIntensity() const { return mDiffuseIntensity; }
      void SetDiffuseIntensity(double aIntensity);
      double GetSpecularIntensity() const { return mSpecularIntensity; }
      void SetSpecularIntensity(double aIntensity);

    private:
      glm::vec3 mColor;

      double mAmbientIntensity;
      double mDiffuseIntensity;
      double mSpecularIntensity;
  };
}

#endif
