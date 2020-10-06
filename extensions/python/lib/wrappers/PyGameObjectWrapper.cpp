#include "PyGameObjectWrapper.hpp"

using py::GameObjectWrapper;

GameObjectWrapper::GameObjectWrapper()
  : GameObject()
{
}

/**
 * Adds a child GameObject. Wrapped for use with Python.
 *
 * @param aObject The GameObject to add.
 */
void GameObjectWrapper::AddChild_(GameObject& aObject)
{
  std::unique_ptr<GameObject> child;
  child.reset(&aObject);
  AddChild(std::move(child));
}

/**
 * Adds a component. Wrapped for use with Python.
 *
 * @param aComponent The Component to add.
 */
void GameObjectWrapper::AddComponent_(Component& aComponent)
{
  std::unique_ptr<Component> comp;
  comp.reset(&aComponent);
  AddComponent(std::move(comp));
}
