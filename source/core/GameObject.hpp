#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "GraphicalComponent.hpp"
#include "Observer.hpp"

namespace core
{
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
      glm::vec4 GetPosition() const  { return mPosition; }

    private:
      std::vector<std::unique_ptr<GameObject>> mChildren;
      std::vector<std::unique_ptr<Component>> mComponents;
      std::vector<std::unique_ptr<GraphicalComponent>> mGraphicalComponents;

      glm::mat4 mTransform;
      glm::vec4 mPosition;
  };
}

#endif
