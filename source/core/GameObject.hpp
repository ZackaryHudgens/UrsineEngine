#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "Observer.hpp"
#include "Signal.hpp"

namespace UrsineCore
{
  class GameObject;

  typedef std::map<std::string, std::unique_ptr<GameObject>> ChildMap;
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

      void Load();
      void Unload();
      void Update();
      void Render();

      std::string GetName() const { return mName; }

      bool AddChild(std::unique_ptr<GameObject> aObject);
      bool RemoveChild(const std::string& aName);
      GameObject* GetChild(const std::string& aName) const;
      std::vector<GameObject*> GetChildren();

      /**
       * Returns a vector containing pointers to all child
       * GameObjects of a given type.
       */
      template<typename T>
      std::vector<T*> GetChildrenOfType() const
      {
        std::vector<T*> children;

        for(const auto& obj : mChildren)
        {
          T* castObj = dynamic_cast<T*>(obj.second.get());
          if(castObj != nullptr)
          {
            children.emplace_back(castObj);
          }
        }

        return children;
      }

      void AddComponent(std::unique_ptr<Component> aComponent);
      std::vector<Component*> GetComponents();

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

      glm::mat4 GetTransform() const;
      glm::vec3 GetPosition() const;

      virtual void Scale(const glm::vec3& aScalar);
      virtual void Translate(const glm::vec3& aVector);
      virtual void Rotate(double aDegrees,
                          const glm::vec3& aAxis);

    private:
      std::string mName;

      ChildMap mChildren;
      ComponentList mComponents;

      glm::mat4 mScalarTransform;
      glm::mat4 mRotationTransform;
      glm::mat4 mTranslationTransform;
  };

  /**
   * GameObject Signals.
   */
  typedef UrsineCore::SignalT<GameObject*> ObjectScaledSignal;
  typedef UrsineCore::SignalT<GameObject*> ObjectMovedSignal;
  typedef UrsineCore::SignalT<GameObject*> ObjectRotatedSignal;

  extern ObjectScaledSignal ObjectScaled;
  extern ObjectMovedSignal ObjectMoved;
  extern ObjectRotatedSignal ObjectRotated;
}

#endif
