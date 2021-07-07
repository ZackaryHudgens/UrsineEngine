#include "Component.hpp"

#include "GameObject.hpp"

#include "Signal.hpp"

using UrsineCore::Component;
using UrsineCore::GameObject;

/******************************************************************************/
Component::Component()
  : mParent(nullptr)
{
}

/******************************************************************************/
void Component::SetParent(UrsineCore::GameObject& aParent)
{
  mParent = &aParent;
}

/******************************************************************************/
GameObject* Component::GetParent() const
{
  return mParent;
}
