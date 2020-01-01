#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "GameObject.hpp"

namespace gCore
{
  class Component : public GameObject
  {
    public:
      Component(GameObject* aParent = nullptr);

      virtual void Update() = 0;
  };
}

#endif
