#include <algorithm>

#include "Scene.hpp"

using UrsineCore::GameObject;
using UrsineCore::Scene;

Scene::Scene()
{
  // Add a default camera to the scene.
  AddObject(std::make_unique<Camera>());

  for(const auto& obj : GetObjectsOfType<Camera>())
  {
    mDefaultCamera = obj;
  }
}

void Scene::Load()
{
  for(auto& object : mObjectMap)
  {
    object.second->Load();
  }
}

void Scene::Unload()
{
  for(auto& object : mObjectMap)
  {
    object.second->Unload();
  }
}

// Updates each GameObject in the scene.
void Scene::Update()
{
  for(auto& object : mObjectMap)
  {
    object.second->Update();
  }
}

void Scene::Render()
{
  for(const auto& object : mObjectMap)
  {
    object.second->Render();
  }
}

/**
 * Adds a GameObject to the Scene.
 *
 * @param aGameObject The GameObject to add.
 * @return True if successfully added; returns false if a GameObject
 *         with the same name is already in the Scene.
 */
bool Scene::AddObject(std::unique_ptr<GameObject> aGameObject)
{
  bool success = true;

  auto foundObject = mObjectMap.find(aGameObject->GetName());
  if(foundObject == mObjectMap.end())
  {
    mObjectMap.emplace(aGameObject->GetName(), std::move(aGameObject));
  }
  else
  {
    success = false;
  }

  return success;
}

/**
 * Removes a GameObject from the Scene.
 *
 * @param aName The name of the GameObject to remove.
 * @return True if successfully removed; returns false if no GameObject
 *         with the given name exists in the Scene.
 */
bool Scene::RemoveObject(const std::string& aName)
{
  bool success = true;

  auto foundObject = mObjectMap.find(aName);
  if(foundObject != mObjectMap.end())
  {
    mObjectMap.erase(foundObject);
  }
  else
  {
    success = false;
  }

  return success;
}

/**
 * Returns a pointer to a GameObject with the given name, if it
 * exists in this Scene.
 *
 * @param aName The name of the desired GameObject.
 * @return A pointer to the GameObject if found, nullptr otherwise.
 */
GameObject* Scene::GetObject(const std::string& aName) const
{
  GameObject* obj = nullptr;

  auto foundObject = mObjectMap.find(aName);
  if(foundObject != mObjectMap.end())
  {
    obj = foundObject->second.get();
  }

  return obj;
}

std::vector<GameObject*> Scene::GetObjects() const
{
  std::vector<GameObject*> objects;

  for(const auto& obj : mObjectMap)
  {
    objects.emplace_back(obj.second.get());
  }

  return objects;
}
