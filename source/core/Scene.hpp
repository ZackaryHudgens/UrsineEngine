#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "Camera.hpp"
#include "GameObject.hpp"

using UrsineRenderer::Camera;

namespace UrsineCore
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
      void Update();
      void Render();

      void AddObject(std::unique_ptr<GameObject> aGameObject);

      std::vector<GameObject*> GetObjects() const;

      /**
       * Returns a vector of all GameObjects of the given type
       * currently in the scene.
       */
      template<typename T>
      std::vector<T*> GetObjectsOfType() const
      {
        std::vector<T*> objects;

        for(const auto& obj : mObjects)
        {
          T* castObj = dynamic_cast<T*>(obj.get());
          if(castObj != nullptr)
          {
            objects.emplace_back(castObj);
          }
        }

        return objects;
      }

      Camera* GetDefaultCamera() const { return mDefaultCamera; }

    private:
      std::vector<std::unique_ptr<GameObject>> mObjects;
      Camera* mDefaultCamera;
  };
}

#endif
