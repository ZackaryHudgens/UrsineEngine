#include <algorithm>

#include "Scene.hpp"

using UrsineCore::GameObject;
using UrsineCore::Scene;

using UrsineRenderer::Camera;

Scene::Scene()
  : mMainCamera(std::make_unique<Camera>())
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

// Adds a GameObject to the scene.
void Scene::AddObject(std::unique_ptr<GameObject> aGameObject)
{
  mObjects.emplace_back(std::move(aGameObject));
}

std::vector<GameObject*> Scene::GetObjects() const
{
  std::vector<GameObject*> objects;

  for(const auto& obj : mObjects)
  {
    objects.emplace_back(obj.get());
  }

  return objects;
}
