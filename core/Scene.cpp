#include <algorithm>

#include "Scene.hpp"

using core::Scene;

Scene::Scene(const std::string& aName)
  : mName(aName)
{
}

void Scene::Load()
{
  for(auto& object : mObjects)
  {
    object->Load();
  }
}

void Scene::Unload()
{
  for(auto& object : mObjects)
  {
    object->Unload();
  }
}

// Adds a GameObject to the scene.
void Scene::AddObject(std::unique_ptr<GameObject> aGameObject)
{
  mObjects.emplace_back(std::move(aGameObject));
}

// Updates each GameObject in the scene.
void Scene::Update()
{
  for(auto& object : mObjects)
  {
    object->Update();
  }
}

void Scene::Render()
{
  for(const auto& object : mObjects)
  {
    object->Render();
  }
}
