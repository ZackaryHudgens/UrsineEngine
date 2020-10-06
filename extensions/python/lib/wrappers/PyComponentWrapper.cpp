#include "PyComponentWrapper.hpp"

using py::ComponentWrapper;

ComponentWrapper::ComponentWrapper()
  : Component()
{
}

/**
 * Calls the Python-overridden "update" method.
 */
void ComponentWrapper::Update()
{
  get_override("update")();
}

/**
 * Calls the Python-overridden "load" method.
 * If this method hasn't been overloaded, this function calls
 * the base Load() method instead.
 */
void ComponentWrapper::Load()
{
  boost::python::override loadFunc = get_override("load");
  if(loadFunc)
  {
    loadFunc();
  }
  else
  {
    Component::Load();
  }
}

/**
 * Calls the Python-overridden "unload" method.
 * If this method hasn't been overloaded, this function calls
 * the base Unload() method instead.
 */
void ComponentWrapper::Unload()
{
  boost::python::override unloadFunc = get_override("unload");
  if(unloadFunc)
  {
    unloadFunc();
  }
  else
  {
    Component::Unload();
  }
}
