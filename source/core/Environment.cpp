#include "Environment.hpp"

#include <cassert>
#include <iostream>

#include <il.h>
#include <ilu.h>

using core::Environment;
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

  // Initialize GLFW
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

      // Initialize GLEW.
      GLenum glewError = glewInit();
      if(glewError != GLEW_OK)
      {
        std::cout << "Error initializing GLEW! "
                  << glewGetErrorString(glewError) << std::endl;
      }
      else
      {
        // Initialize DevIL.
        ilInit();
        ILenum devilError = ilGetError();
        if(devilError != IL_NO_ERROR)
        {
          // TODO: iluErrorString() causes a segfault; why?
          std::cout << "Error initializing DevIL!" << std::endl;
        }
        else
        {
          init = true;

          // Initialize various OpenGL flags.
          glEnable(GL_DEPTH_TEST);

          // Initialize various DevIL flags.
          ilEnable(IL_ORIGIN_SET);
          ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
        }
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

void Environment::Update()
{
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Update();
  }
}

void Environment::Render()
{
  // Clear the window.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render the current scene.
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Render();
  }

  // Swap the front/back buffers.
  glfwSwapBuffers(mWindow);
}
