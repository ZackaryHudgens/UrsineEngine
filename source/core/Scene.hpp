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

      /**
       * Constructor. When called, the Scene creates and adds a default
       * Camera object.
       */
      Scene();

      /**
       * Updates all GameObjects in the Scene.
       */
      void Update();

      /**
       * Renders all GameObjects in the Scene.
       */
      void Render();

      /**
       * Loads all GameObjects in the Scene.
       */
      void Load();

      /**
       * Unloads all GameObjects in the Scene.
       */
      void Unload();

      /**
       * Takes ownership of a given GameObject and adds it to the Scene.
       * This fails if a GameObject with the same name is already in the Scene.
       *
       * @param aGameObject The GameObject to add.
       * @return True if successful, false otherwise.
       */
      bool AddObject(std::unique_ptr<GameObject> aGameObject);

      /**
       * Removes a GameObject from the Scene. This fails if no GameObject with
       * the given name is in the Scene.
       *
       * @param aName The name of the GameObject to remove.
       * @return True if successful, false otherwise.
       */
      bool RemoveObject(const std::string& aName);

      /**
       * Returns a pointer to a GameObject with the given name, if it
       * exists in this Scene.
       *
       * @param aName The name of the desired GameObject.
       * @return A pointer to the GameObject if found, nullptr otherwise.
       */
      GameObject* GetObject(const std::string& aName) const;

      /**
       * Returns all GameObjects in this Scene.
       *
       * @return A vector of pointers to each GameObject in the Scene.
       */
      std::vector<GameObject*> GetObjects() const;

      /**
       * Returns a vector of all GameObjects of the given type
       * currently in the scene.
       *
       * @return A vector of pointers to each GameObject of the given type
       *         in the Scene.
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

      /**
       * Returns a pointer to the default Camera object created during
       * construction.
       *
       * @return A pointer to this Scene's default Camera.
       */
      Camera* GetDefaultCamera() const { return mDefaultCamera; }

    private:
      ObjectMap mObjectMap;
      Camera* mDefaultCamera;
  };
}

#endif
