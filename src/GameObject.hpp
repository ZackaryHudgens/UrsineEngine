#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

namespace gCore
{
  class Component;

  /**
   * A GameObject is essentially just a sack of components.
   * The components themselves are what determine the behavior
   * of the GameObject.
   */
  class GameObject
  {
    public:
      GameObject();

      void Update();
      void ProcessEvent(const SDL_Event& aEvent);

      void AddComponent(std::unique_ptr<Component> aComponent);

    private:
      std::vector<std::unique_ptr<Component>> mComponents;
  };
}

#endif
