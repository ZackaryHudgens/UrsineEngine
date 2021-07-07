#include <algorithm>

#include "Scene.hpp"

using UrsineCore::GameObject;
using UrsineCore::Scene;

/******************************************************************************/
Scene::Scene()
{
  // Add a default camera to the scene.
  AddObject(std::make_unique<Camera>());

  for(const auto& obj : GetObjectsOfType<Camera>())
  {
    mDefaultCamera = obj;
  }
}

/******************************************************************************/
void Scene::Update()
{
  for(auto& object : mObjectMap)
  {
    object.second->Update();
  }
}

/******************************************************************************/
void Scene::Render()
{
  for(const auto& object : mObjectMap)
  {
    object.second->Render();
  }
}

/******************************************************************************/
void Scene::Load()
{
  for(auto& object : mObjectMap)
  {
    object.second->Load();
  }
}

/******************************************************************************/
void Scene::Unload()
{
  for(auto& object : mObjectMap)
  {
    object.second->Unload();
  }
}

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
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

/******************************************************************************/
std::vector<GameObject*> Scene::GetObjects() const
{
  std::vector<GameObject*> objects;

  for(const auto& obj : mObjectMap)
  {
    objects.emplace_back(obj.second.get());
  }

  return objects;
}
