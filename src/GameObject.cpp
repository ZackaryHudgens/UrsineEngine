#include "GameObject.hpp"

#include "Component.hpp"

using gCore::Component;
using gCore::GameObject;

/**
 * Constructor for the base GameObject class.
 */
GameObject::GameObject()
{
}

/**
 * Calls the Update() method for each component.
 */
void GameObject::Update()
{
  for(auto& c : mComponents)
  {
    c->Update();
  }
}

/**
 * Sends an SDL_Event to each component for processing.
 *
 * @param aEvent The event to be processed.
 */
void GameObject::ProcessEvent(const SDL_Event& aEvent)
{
  for(auto& c : mComponents)
  {
    c->ProcessEvent(aEvent);
  }
}

/**
 * Adds a Component to this GameObject, which takes ownership
 * of it.
 *
 * @param aComponent The Component to add.
 */
void GameObject::AddComponent(std::unique_ptr<Component> aComponent)
{
  aComponent->SetParent(this);
  mComponents.emplace_back(std::move(aComponent));
}
