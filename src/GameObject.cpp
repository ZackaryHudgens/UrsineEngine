#include "GameObject.hpp"

#include "CoreObserver.hpp"

using gCore::Component;
using gCore::CoreObserver;
using gCore::GameObject;
using gCore::GraphicalComponent;

/**
 * Constructor for the base GameObject class.
 */
GameObject::GameObject()
  : mLocation(0.0, 0.0)
{
}

/**
 * Calls the Update() method for each Component.
 */
void GameObject::Update()
{
  for(auto& c : mComponents)
  {
    c->Update();
  }

  for(auto& gc : mGraphicalComponents)
  {
    gc->Update();
  }
}

/**
 * Calls the Render() method for each GraphicalComponent.
 */
void GameObject::Render()
{
  for(auto& gc : mGraphicalComponents)
  {
    gc->Render();
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

  for(auto& gc : mGraphicalComponents)
  {
    gc->ProcessEvent(aEvent);
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

  // Keep GraphicalComponents and Components separate for the sake
  // of the Render() function.
  GraphicalComponent* g = dynamic_cast<GraphicalComponent*>(aComponent.get());
  if(g != nullptr)
  {
    // Releases the given pointer from being responsible for deleting
    // the Component...
    aComponent.release();

    // ...so we can create a new unique_ptr to a GraphicalComponent
    // and assign it to that Component. This is done to place the given
    // Component into a vector of GraphicalComponents, since
    // std::unique_ptr<Component> can't be cast to a
    // std::unique_ptr<GraphicalComponent>.
    // TODO: there might be a better way of doing this?
    std::unique_ptr<GraphicalComponent> gPointer;
    gPointer.reset(g);
    mGraphicalComponents.emplace_back(std::move(gPointer));
  }
  else
  {
    mComponents.emplace_back(std::move(aComponent));
  }
}
