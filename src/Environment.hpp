#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <IL/il.h>

#include <memory>

#include "Scene.hpp"

namespace gCore
{
  /**
   * Define "env" as a shorthand to get the Envrionment instance.
   */
  #ifndef env
  #define env Environment::GetInstance()
  #endif

  /**
   * A singleton class that creates an SDL_Window for the game,
   * manages updates and rendering calls for the current scene,
   * and provides a few SDL-related utility functions.
   */
  class Environment
  {
    public:
      static Environment& GetInstance();
      void DeleteInstance();

      bool Initialize(const char* aTitle, int aWidth, int aHeight);

      void Update();
      void RenderScene();

      SDL_Window* GetWindow()     { return mWindowPtr; }
      bool IsQuitting()           { return mIsQuitting; }

      void SetScene(std::unique_ptr<Scene> aScene);
      void SetInternalResolution(int aWidth, int aHeight);

      bool IsKeyPressed(const SDL_Scancode& aScancode);

      double GetTime() { return mCurrentTime; }

    private:
      Environment();
      ~Environment();

      void ProcessSDLEvents();

      static std::unique_ptr<Environment> mInstancePtr;
      std::unique_ptr<Scene> mScenePtr;

      int mInternalWidth;
      int mInternalHeight;

      SDL_Window* mWindowPtr;
      SDL_GLContext mContext;
      bool mIsQuitting;
      double mCurrentTime;
  };
}

#endif
