#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <map>

#include "Camera.hpp"
#include "GameObject.hpp"

namespace gCore
{
  // A scene contains all the objects necessary
  // for a given area in the game.
  class Scene
  {
    public:
      Scene();

      void AddObject(const std::string& aObjectName,
                     std::unique_ptr<GameObject> aGameObject);

      void UpdateObjects();
      void RenderObjects();

      void ProcessSDLEvent(const SDL_Event& aEvent);

    private:
      std::map<std::string, std::unique_ptr<GameObject>> mObjectMap;
      std::unique_ptr<Camera> mCamera;
  };
}

#endif
