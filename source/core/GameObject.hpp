#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "Observer.hpp"

namespace UrsineCore
{
  class GameObject;

  typedef std::vector<std::unique_ptr<GameObject>> ObjectList;
  typedef std::vector<std::unique_ptr<Component>> ComponentList;

  /**
   * A GameObject is essentially just a sack of components.
   * The components themselves are what determine the behavior
   * of the GameObject.
   */
  class GameObject : public Observer
  {
    public:
      GameObject(const std::string& aName);

      void Update();
      void Render();
      void Load();
      void Unload();

      std::string GetName() const { return mName; }

      void AddChild(std::unique_ptr<GameObject> aObject);
      void AddComponent(std::unique_ptr<Component> aComponent);

      glm::mat4 GetTransform() const;
      glm::vec3 GetPosition() const;

      std::vector<GameObject*> GetChildren();
      std::vector<Component*> GetComponents();

      virtual void Scale(const glm::vec3& aScalar);
      virtual void Translate(const glm::vec3& aVector);
      virtual void Rotate(double aDegrees,
                          const glm::vec3& aAxis);

      /**
       * Returns a vector containing pointers to all components
       * of a given type.
       */
      template<typename T>
      std::vector<T*> GetComponentsOfType() const
      {
        std::vector<T*> components;

        for(const auto& comp : mComponents)
        {
          T* castComp = dynamic_cast<T*>(comp.get());
          if(castComp != nullptr)
          {
            components.emplace_back(castComp);
          }
        }

        return components;
      };

    private:
      std::string mName;

      ObjectList mChildren;
      ComponentList mComponents;

      glm::mat4 mScalarTransform;
      glm::mat4 mRotationTransform;
      glm::mat4 mTranslationTransform;
  };
}

#endif
