#include "Component.hpp"

#include "GameObject.hpp"

#include "Signal.hpp"

using UrsineCore::Component;
using UrsineCore::GameObject;

/**
 * The default constuctor for the Component class.
 */
Component::Component()
{
}

void Component::AddChild(std::unique_ptr<Component> aChild)
{
  aChild->SetParent(mParent);
  mChildren.emplace_back(std::move(aChild));
}

void Component::SetParent(GameObject* aParent)
{
  mParent = aParent;

  for(auto& child : mChildren)
  {
    child->SetParent(mParent);
  }
}
