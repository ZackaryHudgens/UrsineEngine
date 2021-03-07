#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "GraphicalComponent.hpp"
#include "Observer.hpp"

using UrsineRenderer::GraphicalComponent;

namespace UrsineCore
{
  class GameObject;

  typedef std::vector<std::unique_ptr<GameObject>> ObjectList;
  typedef std::vector<std::unique_ptr<Component>> ComponentList;
  typedef std::vector<std::unique_ptr<GraphicalComponent>> GraphicalComponentList;

  /**
   * A GameObject is essentially just a sack of components.
   * The components themselves are what determine the behavior
   * of the GameObject.
   *
   * GraphicalComponents are kept separate from other Components
   * so the Render() function doesn't have to iterate over
   * Components that aren't renderable.
   */
  class GameObject : public Observer
  {
    public:
      GameObject();

      void Update();
      void Render();
      void Load();
      void Unload();

      void AddChild(std::unique_ptr<GameObject> aObject);
      void AddComponent(std::unique_ptr<Component> aComponent);

      glm::mat4 GetTransform() const { return mTransform; }
      glm::vec3 GetPosition() const  { return mPosition; }

      std::vector<Component*> GetComponents() const;
      std::vector<GraphicalComponent*> GetGraphicalComponents() const;

      virtual void Scale(const glm::vec3& aScalar);
      virtual void Translate(const glm::vec3& aVector);
      virtual void Rotate(double aDegrees, const glm::vec3& aAxis);

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

        for(const auto& gComp : mGraphicalComponents)
        {
          T* castGComp = dynamic_cast<T*>(gComp.get());
          if(castGComp != nullptr)
          {
            components.emplace_back(castGComp);
          }
        }

        return components;
      };

    private:
      ObjectList mChildren;
      ComponentList mComponents;
      GraphicalComponentList mGraphicalComponents;

      glm::mat4 mTransform;
      glm::vec3 mPosition;
  };
}

#endif
