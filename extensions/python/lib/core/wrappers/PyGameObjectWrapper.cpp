#include "PyGameObjectWrapper.hpp"

#include <iostream>

using py::GameObjectWrapper;
using py::VectorWrapper;

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

/**
 * Scales the GameObject by the given amounts on each axis.
 * Wrapped for use with Python.
 *
 * @param aVector A vector containing the amounts to scale by
 * on each axis (i.e. a vector of {2, 1, 0.5} would scale the object
 * by 2 on the x-axis, by 1 on the y-axis, and by 0.5 on the z-axis).
 */
void GameObjectWrapper::Scale_(const VectorWrapper& aVector)
{
  GameObject::Scale(aVector.GetVec());
}

/**
 * Translates the GameObject by the given amounts on each axis.
 * Wrapped for use with Python.
 *
 * @param aVector The vector to translate this object by.
 */
void GameObjectWrapper::Translate_(const VectorWrapper& aVector)
{
  GameObject::Translate(aVector.GetVec());
}

/**
 * Rotates the GameObject by the given amount in degrees on the given
 * axis. Wrapped for use with Python.
 *
 * @param aDegrees The amount in degrees to rotate by.
 * @param aVector The axis around which to rotate this object.
 */
void GameObjectWrapper::Rotate_(double aDegrees, const VectorWrapper& aVector)
{
  GameObject::Rotate(aDegrees, aVector.GetVec());
}
