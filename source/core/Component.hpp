#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "Observer.hpp"

namespace core
{
  class Component;
  class GameObject;

  typedef std::vector<std::unique_ptr<Component>> ComponentList;

  /**
   * A Component is an interface for any sort of behavior
   * or logic that can be "attached" to a GameObject. Some examples
   * of this behavior include animations, sounds, and input.
   */
  class Component : public Observer
  {
    public:
      Component();

      virtual void Update() {};
      virtual void Load() {}
      virtual void Unload() {}

      virtual void AddChild(std::unique_ptr<Component> aChild);
      const ComponentList& GetChildren() const { return mChildren; }

      void SetParent(GameObject* aParent);
      GameObject* GetParent() const { return mParent; }

    private:
      ComponentList mChildren;

      GameObject* mParent;
  };
}

#endif
