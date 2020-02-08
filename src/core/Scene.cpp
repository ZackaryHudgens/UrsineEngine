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

// Processes an SDLEvent by passing it to each object in the scene.
void Scene::ProcessEvent(const SDL_Event& aEvent)
{
  for(auto& object : mObjectMap)
  {
    object.second->ProcessEvent(aEvent);
  }
}
