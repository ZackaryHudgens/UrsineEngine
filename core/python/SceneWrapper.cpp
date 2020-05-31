#include "SceneWrapper.hpp"

using coreWrappers::SceneWrapper;

SceneWrapper::SceneWrapper()
  : Scene()
{
}

/**
 * Adds an object to the Scene. Wrapped for use with Python.
 *
 * @param aObject The GameObject to add.
 */
void SceneWrapper::AddObject_(GameObject& aObject)
{
  std::unique_ptr<GameObject> object;
  object.reset(&aObject);
  AddObject(std::move(object));
}
