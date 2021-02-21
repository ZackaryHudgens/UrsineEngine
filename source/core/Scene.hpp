#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "Camera.hpp"
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
      void Update();
      void Render();

      void AddObject(std::unique_ptr<GameObject> aGameObject);

      Camera* GetCamera() { return mMainCamera.get(); }

      /**
       * Returns a vector of all GameObjects of the given type
       * currently in the scene.
       */
      template<typename T>
      std::vector<T*> GetObjectsOfType()
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

    private:
      std::vector<std::unique_ptr<GameObject>> mObjects;
      std::unique_ptr<Camera> mMainCamera;
  };
}

#endif
