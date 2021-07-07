#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "GraphicalComponent.hpp"

using UrsineCore::Component;
using UrsineCore::GameObject;

using UrsineRenderer::GraphicalComponent;

/******************************************************************************/
GameObject::GameObject(const std::string& aName)
  : mName(aName)
  , mScalarTransform(1.0f)
  , mRotationTransform(1.0f)
  , mTranslationTransform(1.0f)
{
}

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
std::vector<GameObject*> GameObject::GetChildren()
{
  std::vector<GameObject*> children;

  for(auto& child : mChildren)
  {
    children.emplace_back(child.second.get());
  }

  return children;
}

/******************************************************************************/
void GameObject::AddComponent(std::unique_ptr<Component> aComponent)
{
  aComponent->SetParent(*this);
  mComponents.emplace_back(std::move(aComponent));
}

/******************************************************************************/
std::vector<Component*> GameObject::GetComponents()
{
  std::vector<Component*> comps;

  for(auto& comp : mComponents)
  {
    comps.emplace_back(comp.get());
  }

  return comps;
}

/******************************************************************************/
glm::mat4 GameObject::GetTransform() const
{
  glm::mat4 transform(1.0f);
  transform *= (mTranslationTransform * mRotationTransform * mScalarTransform);
  return transform;
}

/******************************************************************************/
glm::vec3 GameObject::GetPosition() const
{
  glm::vec4 vector(0.0, 0.0, 0.0, 1.0);
  vector = GetTransform() * vector;
  return glm::vec3(vector.x, vector.y, vector.z);
}

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
UrsineCore::ObjectScaledSignal UrsineCore::ObjectScaled;
UrsineCore::ObjectMovedSignal UrsineCore::ObjectMoved;
UrsineCore::ObjectRotatedSignal UrsineCore::ObjectRotated;
