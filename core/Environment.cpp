#include "Environment.hpp"

#include <cassert>
#include <iostream>

using core::Environment;
using core::Extension;
using core::Scene;

std::unique_ptr<Environment> Environment::mInstance = nullptr;

Environment::Environment()
  : mWindow(nullptr)
  , mCurrentScene(nullptr)
  , mInitialized(false)
  , mInternalWidth(0)
  , mInternalHeight(0)
{
}

Environment::~Environment()
{
  glfwTerminate();
}

Environment& Environment::GetInstance()
{
  if(mInstance == nullptr)
  {
    mInstance.reset(new Environment());
  }

  return *mInstance.get();
}

bool Environment::CreateWindow(const char* aTitle, int aWidth, int aHeight)
{
  bool init = false;
  if(glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    mWindow = glfwCreateWindow(aWidth, aHeight, aTitle, nullptr, nullptr);
    if(mWindow == nullptr)
    {
      glfwTerminate();
    }
    else
    {
      glfwMakeContextCurrent(mWindow);
      if(glewInit() == GLEW_OK)
      {
        init = true;
      }
    }
  }

  mInitialized = init;
  return init;
}

void Environment::Run()
{
  if(mInitialized)
  {
    double previousTime = glfwGetTime();
    double updateLag = 0.0;

    while(!glfwWindowShouldClose(mWindow))
    {
      glfwPollEvents();

      double elapsedTime = glfwGetTime() - previousTime;
      previousTime = glfwGetTime();
      updateLag += elapsedTime;

      int updateCounter = 0;
      while(updateLag >= 0.15)
      {
        Update();

        // Update each extension.
        for(auto& ext : mExtensionMap)
        {
          ext.second->Update();
        }

        updateLag -= 0.15;

        ++updateCounter;
        if(updateCounter >= 1000)
        {
          std::cout << "Maximum number of updates reached!" << std::endl;
          break;
        }
      }

      Render();
    }

    glfwDestroyWindow(mWindow);
  }
}

void Environment::LoadScene(Scene& aScene)
{
  // Unload the current scene if there is one.
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Unload();
  }

  mCurrentScene = &aScene;
  mCurrentScene->Load();
}

bool Environment::RegisterExtension(const std::string& aName,
                                    std::unique_ptr<Extension> aExtension)
{
  bool success = false;
  if(mExtensionMap.find(aName) == mExtensionMap.end())
  {
    mExtensionMap.emplace(aName, std::move(aExtension));
    success = true;
  }

  return success;
}

Extension* Environment::GetExtension(const std::string& aName)
{
  Extension* ret = nullptr;

  auto foundExt = mExtensionMap.find(aName);
  if(foundExt != mExtensionMap.end())
  {
    ret = foundExt->second.get();
  }

  return ret;
}

void Environment::Update()
{
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Update();
  }
}

void Environment::Render()
{
  // Render the current scene.
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Render();
  }

  // Clear the window.
  glClear(GL_COLOR_BUFFER_BIT);

  // Swap the front/back buffers.
  glfwSwapBuffers(mWindow);
}
