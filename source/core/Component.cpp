#include "Component.hpp"

#include "GameObject.hpp"

#include "Signal.hpp"

using UrsineCore::Component;

/**
 * The default constuctor for the Component class.
 */
Component::Component()
  : mParent(nullptr)
{
}
