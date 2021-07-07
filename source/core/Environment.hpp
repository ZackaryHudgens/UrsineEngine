#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Signal.hpp"

/**
 * Define "env" as a shorthand to get the Envrionment instance.
 */
#ifndef env
#define env UrsineCore::Environment::GetInstance()
#endif

namespace UrsineCore
{
  /**
   * An enumeration for the different cursor modes supported by GLFW.
   */
  enum class CursorMode
  {
    eNORMAL,
    eHIDDEN,
    eDISABLED
  };

  /**
   * A struct containing information used for various graphical purposes.
   * TODO: allow setting new options without closing and reopening the window
   */
  struct GraphicsOptions
  {
    CursorMode mCursorMode { CursorMode::eDISABLED };

    std::string mTitle     { "UrsineEngine" };

    double mFOV            { 45.0f };
    double mDrawDistance   { 1000.0f };

    int mWidth             { 800 };
    int mHeight            { 600 };
  };

  /**
   * A singleton class that handles creating a valid OpenGL context,
   * a window, and manages scene updating, loading, and unloading.
   */
  class Environment
  {
    public:

      /**
       * Destructor.
       */
      ~Environment();

      /**
       * Accesses the current Environment instance.
       *
       * @return The current Environment instance.
       */
      static Environment& GetInstance();

      /**
       * Intializes the Environment and creates an OpenGL context.
       *
       * @param aInfo Information used in initialization.
       * @return True if initialization was successful; false otherwise.
       */
      bool Initialize(const GraphicsOptions& aOptions);

      /**
       * Begins the game loop. Fails if Initialize() has not already
       * been called.
       *
       * @return True if execution was successful, false otherwise.
       */
      bool Run();

      /**
       * Returns the GLFWWindow object.
       *
       * @return A pointer to the GLFWWindow.
       */
      GLFWwindow* GetWindow() const;

      /**
       * Returns the current time.
       *
       * @return The current time in seconds since initialization.
       */
      double GetTime() const;

      /**
       * Unloads the current scene and loads the given scene.
       *
       * @param aScene The scene to load.
       */
      void LoadScene(Scene& aScene);

      /**
       * Returns the current scene.
       *
       * @return A pointer to the current scene.
       */
      Scene* GetCurrentScene() const;

    protected:

      /**
       * Constructor. This is made protected to implement the Singleton
       * design pattern; there can only ever be one active instance of
       * the Environment class.
       */
      Environment();

    private:

      /**
       * Updates the current scene.
       */
      void Update();

      /**
       * Renders the current scene.
       */
      void Render();

      GLFWwindow* mWindow;

      static std::unique_ptr<Environment> mInstance;
      Scene* mCurrentScene;

      GraphicsOptions mOptions;

      bool mInitialized;
      int mInternalWidth;
      int mInternalHeight;
  };
}

#endif
