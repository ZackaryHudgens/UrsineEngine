#include "Environment.hpp"

#include <iostream>
#include <memory>
#include "AnimationManager.hpp"
#include "Scene.hpp"

using gCore::Scene;
using gCore::GameObject;
using gCore::AnimationManager;
using gCore::Animation;
using gCore::Texture;

int main(int argc, char* args[])
{
  env.Initialize("game!", 480, 270);

  std::unique_ptr<Scene> scene = std::make_unique<Scene>();
  std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
  std::unique_ptr<AnimationManager> aniMan = std::make_unique<AnimationManager>();
  std::unique_ptr<Animation> ani = std::make_unique<Animation>();
  std::unique_ptr<Texture> tex = std::make_unique<Texture>();

  tex->LoadFromFile("resources/bg.jpg");

  ani->SetTexture(std::move(tex));
  ani->AddFrame(SDL_Rect{0, 0, 100, 100});
  ani->AddFrame(SDL_Rect{100, 100, 100, 100});
  ani->SetSpeed(1);

  aniMan->AddAnimation("one", std::move(ani));
  aniMan->SetAnimation("one");

  obj->AddComponent(std::move(aniMan));

  scene->AddObject("obj", std::move(obj));

  env.SetScene(std::move(scene));

  return env.Run();
}

