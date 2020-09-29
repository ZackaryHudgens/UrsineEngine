#include "GraphicalComponentWrapper.hpp"

using py::GraphicalComponentWrapper;

GraphicalComponentWrapper::GraphicalComponentWrapper()
  : GraphicalComponent()
{
}

/**
 * Calls the Python-overridden "update" method.
 */
void GraphicalComponentWrapper::Update()
{
  get_override("update")();
}

/**
 * Calls the Python-overridden "render" method.
 */
void GraphicalComponentWrapper::Render() const
{
  get_override("render")();
}
