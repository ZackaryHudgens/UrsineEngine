#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <map>

#include "GameObject.hpp"

namespace gCore
{
  /**
   * A Scene contains all the GameObjects necessary for a
   * particualr area or level of a game.
   */
  class Scene
  {
    public:
      Scene();

      void AddObject(const std::string& aObjectName,
                     std::unique_ptr<GameObject> aGameObject);

      void Update();
      void Render();
      void ProcessEvent(const SDL_Event& aEvent);

    private:
      std::map<std::string, std::unique_ptr<GameObject>> mObjectMap;
  };
}

#endif
