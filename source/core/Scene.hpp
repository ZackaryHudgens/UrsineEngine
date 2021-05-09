#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "GameObject.hpp"

using UrsineRenderer::Camera;

namespace UrsineCore
{
  typedef std::map<std::string, std::unique_ptr<GameObject>> ObjectMap;

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

      bool AddObject(std::unique_ptr<GameObject> aGameObject);
      bool RemoveObject(const std::string& aName);
      GameObject* GetObject(const std::string& aName) const;
      std::vector<GameObject*> GetObjects() const;

      /**
       * Returns a vector of all GameObjects of the given type
       * currently in the scene.
       */
      template<typename T>
      std::vector<T*> GetObjectsOfType() const
      {
        std::vector<T*> objects;

        for(const auto& obj : mObjectMap)
        {
          T* castObj = dynamic_cast<T*>(obj.second.get());
          if(castObj != nullptr)
          {
            objects.emplace_back(castObj);
          }
        }

        return objects;
      }

      Camera* GetDefaultCamera() const { return mDefaultCamera; }

    private:
      ObjectMap mObjectMap;
      Camera* mDefaultCamera;
  };
}

#endif
