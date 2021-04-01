#include "Environment.hpp"

#include <cassert>
#include <iostream>

#include <il.h>
#include <ilu.h>

#include "CoreSignals.hpp"

using UrsineCore::Environment;
using UrsineCore::Scene;

std::unique_ptr<Environment> Environment::mInstance = nullptr;

/**
 * GLFW input callback functions.
 */
namespace inputCallbacks
{
  void GLFWFramebufferSizeCallback(GLFWwindow* aWindow,
                                   int aWidth,
                                   int aHeight)
  {
    glViewport(0, 0, aWidth, aHeight);
  }

  void GLFWKeyPressedCallback(GLFWwindow* aWindow,
                              int aKey,
                              int aScancode,
                              int aAction,
                              int aMods)
  {
    UrsineCore::InputAction action = (UrsineCore::InputAction)aAction;

    switch(action)
    {
      case UrsineCore::InputAction::ePRESSED:
      {
        UrsineCore::KeyPressed.Notify((UrsineCore::KeyCode)aKey, aMods);
        break;
      }
      case UrsineCore::InputAction::eRELEASED:
      {
        UrsineCore::KeyReleased.Notify((UrsineCore::KeyCode)aKey, aMods);
        break;
      }
      case UrsineCore::InputAction::eREPEATED:
      {
        UrsineCore::KeyRepeated.Notify((UrsineCore::KeyCode)aKey, aMods);
        break;
      }
      default:
      {
        break;
      }
    }
  }

  void GLFWMouseMovedCallback(GLFWwindow* aWindow,
                              double aXPosition,
                              double aYPosition)
  {
    UrsineCore::MouseMoved.Notify(aXPosition, aYPosition);
  }

  void GLFWMouseEnteredOrLeftCallback(GLFWwindow* aWindow,
                                      int aEntered)
  {
    bool entered = false;

    if(aEntered)
    {
      entered = true;
    }

    UrsineCore::MouseEnteredOrLeft.Notify(entered);
  }

  void GLFWMouseButtonPressedCallback(GLFWwindow* aWindow,
                                      int aButton,
                                      int aAction,
                                      int aMods)
  {
    UrsineCore::InputAction action = (UrsineCore::InputAction)aAction;

    switch(action)
    {
      case UrsineCore::InputAction::ePRESSED:
      {
        UrsineCore::MouseButtonPressed.Notify((UrsineCore::MouseButton)aButton, aMods);
        break;
      }
      case UrsineCore::InputAction::eRELEASED:
      {
        UrsineCore::MouseButtonReleased.Notify((UrsineCore::MouseButton)aButton, aMods);
        break;
      }
      case UrsineCore::InputAction::eREPEATED:
      default:
      {
        break;
      }
    }
  }

  void GLFWMouseScrolledCallback(GLFWwindow* aWindow,
                                 double aXOffset,
                                 double aYOffset)
  {
    UrsineCore::MouseScrolled.Notify(aXOffset, aYOffset);
  }
}

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

bool Environment::CreateWindow(const std::string& aTitle, int aWidth, int aHeight)
{
  bool init = false;

  // Initialize GLFW
  if(glfwInit())
  {
    // Set the desired OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Use the core profile only; this removes backwards-compatible features
    // that are no longer needed for the engine.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable forward compatibility; this removes all deprecated features
    // in the desired version of OpenGL (3.3).
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    mWindow = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
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

          // Connect GLFW callback functions.
          glfwSetFramebufferSizeCallback(mWindow, inputCallbacks::GLFWFramebufferSizeCallback);
          glfwSetKeyCallback(mWindow, inputCallbacks::GLFWKeyPressedCallback);
          glfwSetCursorPosCallback(mWindow, inputCallbacks::GLFWMouseMovedCallback);
          glfwSetCursorEnterCallback(mWindow, inputCallbacks::GLFWMouseEnteredOrLeftCallback);
          glfwSetMouseButtonCallback(mWindow, inputCallbacks::GLFWMouseButtonPressedCallback);
          glfwSetScrollCallback(mWindow, inputCallbacks::GLFWMouseScrolledCallback);

          // Set the viewport to the entire window.
          glViewport(0, 0, aWidth, aHeight);

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
