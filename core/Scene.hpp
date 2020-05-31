#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "GameObject.hpp"

namespace core
{
  /**
   * A Scene contains all the GameObjects necessary for a
   * particular area or level of a game.
   */
  class Scene
  {
    public:
      Scene();

      void Load();
      void Unload();

      void AddObject(std::unique_ptr<GameObject> aGameObject);

      void Update();
      void Render();

    private:
      std::vector<std::unique_ptr<GameObject>> mObjects;
  };
}

#endif
