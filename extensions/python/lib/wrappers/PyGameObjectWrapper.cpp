#include "PyGameObjectWrapper.hpp"

#include <iostream>

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

/**
 * Scales the GameObject by the given amounts on each axis.
 * Wrapped for use with Python.
 *
 * @param aArgs A python list of arguments. The first three are expected
 * to be convertible to doubles (x, y, and z values, in that order);
 * otherwise this function raises an exception.
 */
void GameObjectWrapper::Scale_(const bp::list& aArgs)
{
  try
  {
    double& x = bp::extract<double&>(aArgs[0]);
    double& y = bp::extract<double&>(aArgs[1]);
    double& z = bp::extract<double&>(aArgs[2]);

    GameObject::Scale(glm::vec3(x, y, z));
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}

/**
 * Translates the GameObject by the given amounts on each axis.
 * Wrapped for use with Python.
 *
 * @param aArgs A python list of arguments. The first three are expected
 * to be convertible to doubles (x, y, and z values, in that order);
 * otherwise this function raises an exception.
 */
void GameObjectWrapper::Translate_(const bp::list& aArgs)
{
  try
  {
    double& x = bp::extract<double&>(aArgs[0]);
    double& y = bp::extract<double&>(aArgs[1]);
    double& z = bp::extract<double&>(aArgs[2]);

    GameObject::Translate(glm::vec3(x, y, z));
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}

/**
 * Rotates the GameObject by the given amount in degrees on the given
 * axis. Wrapped for use with Python.
 *
 * @param aDegrees The amount in degrees to rotate by.
 * @param aArgs A python list of arguments. The first three are expected
 * to be convertible to doubles (x, y, and z values, in that order);
 * otherwise this function raises an exception.
 */
void GameObjectWrapper::Rotate_(double aDegrees, const bp::list& aArgs)
{
  try
  {
    double& x = bp::extract<double&>(aArgs[0]);
    double& y = bp::extract<double&>(aArgs[1]);
    double& z = bp::extract<double&>(aArgs[2]);

    GameObject::Rotate(aDegrees, glm::vec3(x, y, z));
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}
