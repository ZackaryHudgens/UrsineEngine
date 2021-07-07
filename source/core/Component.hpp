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

      /**
       * Constructor.
       */
      Component();

      /**
        * A virtual function that gets called at regular intervals.
        * Should be overridden by inheriting components to provide
        * functionality.
        */
      virtual void Update() {}

      /**
       * A virtual function that gets called whenever the scene
       * is first loaded.
       */
      virtual void Load() {}

      /**
       * A virtual function that gets called right before the
       * scene is unloaded.
       */
      virtual void Unload() {}

      /**
       * Attaches this component to a GameObject.
       *
       * @param aParent The GameObject to attach to.
       */
      void SetParent(GameObject& aParent);

      /**
       * Returns the GameObject this component is attached to.
       *
       * @return A pointer to the parent GameObject.
       */
      GameObject* GetParent() const;

    private:
      GameObject* mParent;
  };
}

#endif
