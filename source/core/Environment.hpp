#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

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
   * An enumeration for the three supported types of windows in GLFW.
   */
  enum class WindowMode
  {
    eWINDOWED,
    eFULLSCREEN,
    eBORDERLESS_FULLSCREEN
  };

  /**
   * An enumeration for each supported GLFW cursor mode, defined
   * in the same order as GLFW and assigned the same value.
   */
  enum CursorMode
  {
    eNORMAL = 0x00034001,
    eHIDDEN = 0x00034002,
    eDISABLED = 0x00034003
  };

  /**
   * A struct containing information used for various graphical purposes.
   */
  struct GraphicsOptions
  {
    CursorMode mCursorMode { CursorMode::eDISABLED };
    WindowMode mWindowMode { WindowMode::eWINDOWED };

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
      GLFWwindow* GetWindow() const { return mWindow; }

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
      Scene* GetCurrentScene() const { return mCurrentScene; }

      /**
       * Returns the current Field of View value in degrees.
       *
       * @return The current Field of View.
       */
      double GetFOV() const { return mFOV; }

      /**
       * Returns the current draw distance.
       *
       * @return The current draw distance.
       */
      double GetDrawDistance() const { return mDrawDistance; }

      /**
       * Returns a pointer to the font library. Used by TextComponents
       * to load fonts with Freetype.
       *
       * @return A pointer to the Freetype font library.
       */
      FT_Library* GetFontLibrary() { return &mFontLibrary; }

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

      FT_Library mFontLibrary;

      static std::unique_ptr<Environment> mInstance;
      Scene* mCurrentScene;

      GraphicsOptions mOptions;

      bool mInitialized;

      double mFOV;
      double mDrawDistance;
  };
}

#endif
