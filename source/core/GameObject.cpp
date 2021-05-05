#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

using UrsineCore::Component;
using UrsineCore::GameObject;

using UrsineRenderer::GraphicalComponent;

/**
 * Constructor for the base GameObject class.
 */
GameObject::GameObject()
  : mScalarTransform(1.0f)
  , mRotationTransform(1.0f)
  , mTranslationTransform(1.0f)
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
  aComponent->SetParent(*this);

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
 * Returns a matrix containing all transformations that have been applied
 * to this object.
 *
 * @return A transformation matrix for this object.
 */
glm::mat4 GameObject::GetTransform() const
{
  glm::mat4 transform(1.0f);
  transform *= (mTranslationTransform * mRotationTransform * mScalarTransform);
  return transform;
}

/**
 * Returns a vector representing this object's position in 3D space
 * by multiplying it with its transformation matrix.
 *
 * @return This object's position in 3D space.
 */
glm::vec3 GameObject::GetPosition() const
{
  glm::vec4 vector(0.0, 0.0, 0.0, 1.0);
  vector = GetTransform() * vector;
  return glm::vec3(vector.x, vector.y, vector.z);
}

/**
 * Returns a list of pointers to all child GameObjects.
 *
 * @return A list of child GameObjects.
 */
std::vector<GameObject*> GameObject::GetChildren()
{
  std::vector<GameObject*> children;

  for(auto& child : mChildren)
  {
    children.emplace_back(child.get());
  }

  return children;
}

/**
 * Returns a list of pointers to all Components.
 *
 * @return A list of Components.
 */
std::vector<Component*> GameObject::GetComponents()
{
  std::vector<Component*> comps;

  for(auto& comp : mComponents)
  {
    comps.emplace_back(comp.get());
  }

  return comps;
}

/**
 * Returns a list of pointers to all GraphicalComponents.
 *
 * @return A list of GraphicalComponents.
 */
std::vector<GraphicalComponent*> GameObject::GetGraphicalComponents()
{
  std::vector<GraphicalComponent*> gComps;

  for(auto& gComp : mGraphicalComponents)
  {
    gComps.emplace_back(gComp.get());
  }

  return gComps;
}

/**
 * Scales the GameObject's transform by the given amount.
 *
 * @param aScalar The amount to scale by on each axis.
 */
void GameObject::Scale(const glm::vec3& aScalar)
{
  mScalarTransform = glm::scale(mScalarTransform, aScalar);
}

/**
 * Translates this GameObject's transform in the given direction.
 *
 * @param aVector The vector to translate to.
 */
void GameObject::Translate(const glm::vec3& aVector)
{
  mTranslationTransform = glm::translate(glm::mat4(1.0f), aVector);
}

/**
 * Rotates this GameObject's transform by the given amount around
 * the given axis.
 *
 * @param aDegrees The amount to rotate by in degrees.
 * @param aAxis The axis around which to rotate.
 * @param aSpace The space in which to roate the object (world or local).
 */
void GameObject::Rotate(double aDegrees,
                        const glm::vec3& aAxis)
{
  mRotationTransform = glm::rotate(mRotationTransform,
                                   (float)glm::radians(aDegrees),
                                   aAxis);
}
