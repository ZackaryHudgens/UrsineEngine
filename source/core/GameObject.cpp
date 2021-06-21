#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "GraphicalComponent.hpp"

using UrsineCore::Component;
using UrsineCore::GameObject;

using UrsineRenderer::GraphicalComponent;

/**
 * Constructor for the base GameObject class.
 */
GameObject::GameObject(const std::string& aName)
  : mName(aName)
  , mScalarTransform(1.0f)
  , mRotationTransform(1.0f)
  , mTranslationTransform(1.0f)
{
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

  for(auto& child : mChildren)
  {
    child.second->Load();
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

  for(auto& child : mChildren)
  {
    child.second->Unload();
  }
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

  for(auto& child : mChildren)
  {
    child.second->Update();
  }
}

/**
 * Calls the Render() method for each GraphicalComponent and child.
 */
void GameObject::Render()
{
  for(auto& c : mComponents)
  {
    GraphicalComponent* gc = dynamic_cast<GraphicalComponent*>(c.get());
    if(gc != nullptr)
    {
      gc->Render();
    }
  }

  for(auto& child : mChildren)
  {
    child.second->Render();
  }
}

/**
 * Adds a child GameObject.
 *
 * @param aObject The GameObject to add.
 * @return True if the GameObject was added successfully,
 *         false otherwise.
 */
bool GameObject::AddChild(std::unique_ptr<GameObject> aObject)
{
  bool success = true;

  auto foundChild = mChildren.find(aObject->GetName());
  if(foundChild == mChildren.end())
  {
    mChildren.emplace(aObject->GetName(), std::move(aObject));
  }
  else
  {
    success = false;
  }

  return success;
}

/**
 * Removes a child GameObject.
 *
 * @param aName The name of the GameObject to remove.
 * @return True if the GameObject was removed successfully,
 *         false otherwise.
 */
bool GameObject::RemoveChild(const std::string& aName)
{
  bool success = true;

  auto foundChild = mChildren.find(aName);
  if(foundChild != mChildren.end())
  {
    mChildren.erase(foundChild);
  }
  else
  {
    success = false;
  }

  return success;
}

/**
 * Returns a pointer to a child GameObject with the given name,
 * if it exists.
 *
 * @param aName The name of the desired child GameObject.
 * @return A pointer to the GameObject if found, nullptr otherwise.
 */
GameObject* GameObject::GetChild(const std::string& aName) const
{
  GameObject* obj = nullptr;

  auto foundChild = mChildren.find(aName);
  if(foundChild != mChildren.end())
  {
    obj = foundChild->second.get();
  }

  return obj;
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
    children.emplace_back(child.second.get());
  }

  return children;
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
  mComponents.emplace_back(std::move(aComponent));
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
 * Scales the GameObject's transform by the given amount.
 *
 * @param aScalar The amount to scale by on each axis.
 */
void GameObject::Scale(const glm::vec3& aScalar)
{
  mScalarTransform = glm::scale(mScalarTransform, aScalar);
  ObjectScaled.Notify(this);

  // Scale each child object.
  for(auto& child : mChildren)
  {
    child.second->Scale(aScalar);
  }
}

/**
 * Translates this GameObject's transform in the given direction.
 *
 * @param aVector The vector to translate to.
 */
void GameObject::Translate(const glm::vec3& aVector)
{
  mTranslationTransform = glm::translate(mTranslationTransform, aVector);
  ObjectMoved.Notify(this);

  // Transform each child object relative to this object.
  for(auto& child : mChildren)
  {
    child.second->Translate((child.second->GetPosition() + GetPosition()));
  }
}

/**
 * Rotates this GameObject's transform by the given amount around
 * the given axis.
 *
 * @param aDegrees The amount to rotate by in degrees.
 * @param aAxis The axis around which to rotate.
 */
void GameObject::Rotate(double aDegrees,
                        const glm::vec3& aAxis)
{
  mRotationTransform = glm::rotate(mRotationTransform,
                                   (float)glm::radians(aDegrees),
                                   aAxis);
  ObjectRotated.Notify(this);

  // Rotate each child object.
  for(auto& child : mChildren)
  {
    child.second->Rotate(aDegrees, aAxis);
  }
}

/**
 * Creates a new scalar transform for this GameObject.
 *
 * @param aScalar The amount to scale by on each axis.
 */
void GameObject::SetScale(const glm::vec3& aScalar)
{
  mScalarTransform = glm::scale(glm::mat4(1.0), aScalar);
  ObjectScaled.Notify(this);

  // Create a new scalar transform for each child object.
  for(auto& child : mChildren)
  {
    child.second->SetScale(aScalar);
  }
}

/**
 * Sets the position of this GameObject by creating a new translation
 * transform.
 *
 * @param aVector The position to move to.
 */
void GameObject::SetPosition(const glm::vec3& aVector)
{
  mTranslationTransform = glm::translate(glm::mat4(1.0), aVector);
  ObjectMoved.Notify(this);

  // Transform each child object relative to this object.
  for(auto& child : mChildren)
  {
    child.second->SetPosition((child.second->GetPosition() + GetPosition()));
  }
}

/**
 * Creates a new rotation transform for this GameObject using the given
 * axis of rotation.
 *
 * @param aDegrees The amount to rotate by in degrees.
 * @param aAxis The axis around which to rotate.
 */
void GameObject::SetRotation(double aDegrees,
                             const glm::vec3& aAxis)
{
  mRotationTransform = glm::rotate(glm::mat4(1.0),
                                   (float)glm::radians(aDegrees),
                                   aAxis);
  ObjectRotated.Notify(this);

  // Set the rotation of each child object.
  for(auto& child : mChildren)
  {
    child.second->SetRotation(aDegrees, aAxis);
  }
}

/**
 * GameObject Signals.
 */
UrsineCore::ObjectScaledSignal UrsineCore::ObjectScaled;
UrsineCore::ObjectMovedSignal UrsineCore::ObjectMoved;
UrsineCore::ObjectRotatedSignal UrsineCore::ObjectRotated;
