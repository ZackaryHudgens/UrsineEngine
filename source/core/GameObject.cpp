#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

using UrsineCore::Component;
using UrsineCore::GameObject;

using UrsineRenderer::GraphicalComponent;

/**
 * Constructor for the base GameObject class.
 */
GameObject::GameObject()
  : mTransform(1.0f)
  , mPosition(0.0f, 0.0f, 0.0f)
{
}

/**
 * Calls the Update() method for each Component and child.
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

  for(auto& child : mChildren)
  {
    child->Update();
  }
}

/**
 * Calls the Render() method for each GraphicalComponent and child.
 */
void GameObject::Render()
{
  for(auto& gc : mGraphicalComponents)
  {
    gc->Render();
  }

  for(auto& child : mChildren)
  {
    child->Render();
  }
}

/**
 * Calls the Load() method for each Component and child.
 */
void GameObject::Load()
{
  for(auto& c : mComponents)
  {
    c->Load();
  }

  for(auto& gc : mGraphicalComponents)
  {
    gc->Load();
  }

  for(auto& child : mChildren)
  {
    child->Load();
  }
}

/**
 * Calls the Unload() method for each Component and child.
 */
void GameObject::Unload()
{
  for(auto& c : mComponents)
  {
    c->Unload();
  }

  for(auto& gc : mGraphicalComponents)
  {
    gc->Unload();
  }

  for(auto& child : mChildren)
  {
    child->Unload();
  }
}

/**
 * Adds a child GameObject.
 *
 * @param aObject The GameObject to add.
 */
void GameObject::AddChild(std::unique_ptr<GameObject> aObject)
{
  mChildren.emplace_back(std::move(aObject));
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

  // Keep GraphicalComponents and regular Components separate to optimize
  // the Render() function.
  GraphicalComponent* g = dynamic_cast<GraphicalComponent*>(aComponent.get());
  if(g != nullptr)
  {
    // Releases the given pointer from being responsible for deleting
    // the Component...
    aComponent.release();

    // ...so we can create a new unique_ptr to a GraphicalComponent
    // and assign it to that Component. This is done to place the given
    // Component into a vector of GraphicalComponents, since
    // std::unique_ptr can't be cast to another type.
    std::unique_ptr<GraphicalComponent> gPointer;
    gPointer.reset(g);
    mGraphicalComponents.emplace_back(std::move(gPointer));
  }
  else
  {
    mComponents.emplace_back(std::move(aComponent));
  }
}

/**
 * Scales the GameObject's transform by the given amount.
 *
 * @param aScalar The amount to scale by on each axis.
 */
void GameObject::Scale(const glm::vec3& aScalar)
{
  mTransform = glm::scale(mTransform, aScalar);
}

/**
 * Translates this GameObject's transform in the given direction.
 *
 * @param aVector The vector to translate by.
 */
void GameObject::Translate(const glm::vec3& aVector)
{
  mPosition += aVector;
  mTransform = glm::translate(mTransform, aVector);
}

/**
 * Rotates this GameObject's transform by the given amount around
 * the given axis.
 *
 * @param aDegrees The amount to rotate by in degrees.
 * @param aAxis The axis around which to rotate.
 */
void GameObject::Rotate(double aDegrees, const glm::vec3& aAxis)
{
  mTransform = glm::rotate(mTransform, (float)glm::radians(aDegrees), aAxis);
}
