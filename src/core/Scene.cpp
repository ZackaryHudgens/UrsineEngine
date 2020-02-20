#include <algorithm>

#include "Scene.hpp"

using gCore::Scene;

Scene::Scene()
{
}

// Adds a GameObject to the scene.
void Scene::AddObject(const std::string& aObjectName,
                      std::unique_ptr<GameObject> aGameObject)
{
  if(aGameObject != nullptr)
  {
    mObjectMap.emplace(aObjectName, std::move(aGameObject));
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

