#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <vector>

#include "Component.hpp"
#include "GraphicalComponent.hpp"
#include "Observer.hpp"
#include "Vector2D.hpp"

using math::Vector2D;

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

      Vector2D GetLocation() const { return mLocation; }

    private:
      std::vector<std::unique_ptr<GameObject>> mChildren;
      std::vector<std::unique_ptr<Component>> mComponents;
      std::vector<std::unique_ptr<GraphicalComponent>> mGraphicalComponents;

      Vector2D mLocation;
  };
}

#endif
