#include "Environment.hpp"

#include <iostream>

#include <il.h>
#include <ilu.h>

#include "CoreSignals.hpp"

using UrsineCore::Environment;
using UrsineCore::Scene;

std::unique_ptr<Environment> Environment::mInstance = nullptr;

/**
 * GLFW input callback functions.
 *
 * These are called whenever glfwPollEvents() processes the appropriate event.
 * Note that glfwPollEvents() is called once per Update cycle in Run().
 */
namespace inputCallbacks
{
  /**
   * Called when the window is resized.
   *
   * @param aWindow The window that was resized.
   * @param aWidth The new width of the window.
   * @param aHeight The new height of the window.
   */
  void GLFWFramebufferSizeCallback(GLFWwindow* aWindow,
                                   int aWidth,
                                   int aHeight)
  {
    glViewport(0, 0, aWidth, aHeight);
  }

  /**
   * Called when a key is pressed, released, or held long enough
   * to trigger a repeated entry.
   *
   * @param aWindow The window in focus.
   * @param aKey The key as recognized by GLFW.
   * @param aScancode The unique key identifier.
   * @param aAction Whether the key was pressed, released, or held.
   * @param aMods Any active modifications (i.e. Shift, Control, etc.)
   */
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

  /**
   * Called whenever the mouse moves within the confines of the window.
   * Positions are relative to the window.
   *
   * @param aWindow The window in question.
   * @param aXPosition The new X position of the mouse cursor.
   * @param aYPosition The new Y position of the mouse cursor.
   */
  void GLFWMouseMovedCallback(GLFWwindow* aWindow,
                              double aXPosition,
                              double aYPosition)
  {
    UrsineCore::MouseMoved.Notify(aXPosition, aYPosition);
  }

  /**
   * Called whenever the mouse enters or leaves the window.
   *
   * @param aWindow The window in question.
   * @param aEntered Whether the mouse entered or left the window.
   */
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

  /**
   * Called whenever a button on the mouse is pressed, released,
   * or held long enough to trigger a repeated entry.
   *
   * @param aWindow The window in question.
   * @param aButton The button identifier.
   * @param aAction Whether the button was pressed, released, or held.
   * @param aMods Any active modifications (i.e. Shift, Control, etc.)
   */
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

  /**
   * Called whenever the mouse is scrolled.
   *
   * @param aWindow The focused window.
   * @param aXOffset The amount scrolled in the x-direction
   *                 (usually with a touchpad)
   * @param aYOffset The amount scrolled in the y-direction.
   */
  void GLFWMouseScrolledCallback(GLFWwindow* aWindow,
                                 double aXOffset,
                                 double aYOffset)
  {
    UrsineCore::MouseScrolled.Notify(aXOffset, aYOffset);
  }
}

/*****************************************************************************/
Environment::Environment()
  : mWindow(nullptr)
  , mCurrentScene(nullptr)
  , mInitialized(false)
  , mFOV(45.0)
  , mDrawDistance(1000.0)
{
}

/*****************************************************************************/
Environment::~Environment()
{
  glfwTerminate();
}

/*****************************************************************************/
Environment& Environment::GetInstance()
{
  if(mInstance == nullptr)
  {
    mInstance.reset(new Environment());
  }

  return *mInstance.get();
}

/*****************************************************************************/
bool Environment::Initialize(const GraphicsOptions& aOptions)
{
  bool init = false;

  if(!mInitialized)
  {
    // Initialize GLFW.
    if(glfwInit())
    {
      // Set the desired OpenGL version to 3.3.
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

      // Use the core profile only; this removes backwards-compatible features
      // that are no longer needed for the engine.
      glfwWindowHint(GLFW_OPENGL_PROFILE,
                     GLFW_OPENGL_CORE_PROFILE);

      // Enable forward compatibility; this removes all deprecated features
      // in the desired version of OpenGL (3.3).
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                     GLFW_TRUE);

      // Create the window.
      switch(aOptions.mWindowMode)
      {
        case WindowMode::eWINDOWED:
        {
          mWindow = glfwCreateWindow(aOptions.mWidth,
                                     aOptions.mHeight,
                                     aOptions.mTitle.c_str(),
                                     nullptr,
                                     nullptr);
          break;
        }
        case WindowMode::eFULLSCREEN:
        {
          mWindow = glfwCreateWindow(aOptions.mWidth,
                                     aOptions.mHeight,
                                     aOptions.mTitle.c_str(),
                                     glfwGetPrimaryMonitor(),
                                     nullptr);
          break;
        }
        case WindowMode::eBORDERLESS_FULLSCREEN:
        {
          const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

          glfwWindowHint(GLFW_RED_BITS, mode->redBits);
          glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
          glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
          glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

          mWindow = glfwCreateWindow(mode->width,
                                     mode->height,
                                     aOptions.mTitle.c_str(),
                                     glfwGetPrimaryMonitor(),
                                     nullptr);
          break;
        }
        default:
        {
          break;
        }
      }

      if(mWindow == nullptr)
      {
        std::cout << "Error creating window! " << std::endl;
        glfwTerminate();
      }
      else
      {
        // Create the OpenGL context.
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
            std::cout << "Error initializing DevIL!" << std::endl;
                      //<< iluErrorString(devilError) << std::endl;
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

            // Set the GLFW cursor input mode.
            glfwSetInputMode(mWindow, GLFW_CURSOR, aOptions.mCursorMode);

            // Set the viewport to the entire window.
            glViewport(0, 0, aOptions.mWidth, aOptions.mHeight);

            // Set various Environment values.
            mFOV = aOptions.mFOV;
            mDrawDistance = aOptions.mDrawDistance;

            // Initialize various OpenGL flags.
            glEnable(GL_DEPTH_TEST);

            // Initialize various DevIL flags.
            ilEnable(IL_ORIGIN_SET);
            ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
          }
        }
      }
    }
  }
  else
  {
    // The Environment has already been initialized, so we need only apply
    // the new graphics settings.

    // Update the window mode.
    switch(aOptions.mWindowMode)
    {
      case WindowMode::eWINDOWED:
      {
        glfwSetWindowMonitor(mWindow,
                             nullptr,
                             0,
                             0,
                             aOptions.mWidth,
                             aOptions.mHeight,
                             GLFW_DONT_CARE);
        break;
      }
      case WindowMode::eFULLSCREEN:
      {
        glfwSetWindowMonitor(mWindow,
                             glfwGetPrimaryMonitor(),
                             0,
                             0,
                             aOptions.mWidth,
                             aOptions.mHeight,
                             GLFW_DONT_CARE);
        break;
      }
      case WindowMode::eBORDERLESS_FULLSCREEN:
      {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(mWindow,
                             glfwGetPrimaryMonitor(),
                             0,
                             0,
                             mode->width,
                             mode->height,
                             mode->refreshRate);
        break;
      }
      default:
      {
        break;
      }
    }
    
    // Set the GLFW cursor input mode.
    glfwSetInputMode(mWindow, GLFW_CURSOR, aOptions.mCursorMode);

    // Set the window title.
    glfwSetWindowTitle(mWindow, aOptions.mTitle.c_str());

    // Set the viewport to the entire window.
    glViewport(0, 0, aOptions.mWidth, aOptions.mHeight);

    // Set various Environment values.
    mFOV = aOptions.mFOV;
    mDrawDistance = aOptions.mDrawDistance;
  }

  mInitialized = init;
  return init;
}

/*****************************************************************************/
bool Environment::Run()
{
  bool success = true;

  if(mInitialized)
  {
    while(!glfwWindowShouldClose(mWindow))
    {
      glfwPollEvents();
      Update();
      Render();
    }

    glfwDestroyWindow(mWindow);
  }
  else
  {
    success = false;
  }

  return success;
}

/*****************************************************************************/
double Environment::GetTime() const
{
  return glfwGetTime();
}

/*****************************************************************************/
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

/*****************************************************************************/
void Environment::Update()
{
  if(mCurrentScene != nullptr)
  {
    mCurrentScene->Update();
  }
}

/*****************************************************************************/
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
