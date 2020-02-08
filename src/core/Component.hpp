#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SDL2/SDL.h>

namespace gCore
{
  class GameObject;

  /**
   * A Component is an interface for any sort of behavior
   * or logic that can be "attached" to a GameObject. Some examples
   * of this behavior include animations, sounds, and input.
   *
   * Each different type of Component will need to implement their own
   * Update() and ProcessEvent() logic.
   */
  class Component
  {
    public:
      Component();

      virtual void Update() = 0;
      virtual void ProcessEvent(const SDL_Event& aEvent) = 0;

      void SetParent(GameObject* aParent) { mParent = aParent; }
      GameObject* GetParent() const       { return mParent; }

    private:
      GameObject* mParent;
  };
}

#endif
