#include <algorithm>

#include "Scene.hpp"

using gCore::Scene;

Scene::Scene()
  : mCamera(new Camera())
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
void Scene::UpdateObjects()
{
  for(auto& object : mObjectMap)
  {
    object.second->Update();
  }

  mCamera->Update();
}

void Scene::RenderObjects()
{
  for(const auto& object : mObjectMap)
  {
    object.second->Render(*mCamera);
  }
}

// Processes an SDLEvent by passing it to each object in the scene.
void Scene::ProcessSDLEvent(const SDL_Event& aEvent)
{
  for(auto& object : mObjectMap)
  {
    object.second->ProcessSDLEvent(aEvent);
  }
}
