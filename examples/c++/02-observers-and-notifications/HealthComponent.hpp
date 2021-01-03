#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "Component.hpp"

namespace example
{
  class HealthComponent : public core::Component
  {
    public:
      HealthComponent();

      void Update() override;

    private:
      int mHealth;
  };
}

#endif
