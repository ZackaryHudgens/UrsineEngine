#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "Observer.hpp"

namespace UrsineCore
{
  class GameObject;

  /**
   * A Component is an interface for any sort of behavior
   * or logic that can be "attached" to a GameObject. Some examples
   * of this behavior include animations, sounds, and input.
   */
  class Component : public Observer
  {
    public:
      Component();

      /**
        * A virtual function that 
        */
      virtual void Update() {}
      virtual void Load() {}    // Called when the scene is loaded
      virtual void Unload() {}  // Called when the scene is unloaded

      void SetParent(GameObject& aParent) { mParent = &aParent; }
      GameObject* GetParent() const       { return mParent; }

    private:
      GameObject* mParent;
  };
}

#endif
