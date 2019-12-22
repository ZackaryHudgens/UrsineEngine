#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

/**
 * Define "env" as a shorthand to get the Envrionment instance.
 */
#ifndef env
#define env Environment::GetInstance()
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <IL/il.h>

#include <memory>

#include "Scene.hpp"

/**
 * A singleton class that creates an SDL_Window for the game,
 * manages updates and rendering calls for the current scene,
 * and provides a few SDL-related utility functions.
 */
class Environment
{
  public:
    ~Environment();

    static Environment* GetInstance();
    static void DeleteInstance();

    static bool Initialize(const char* aTitle, int aWidth, int aHeight);

    static void Update();
    static void RenderScene();

    static SDL_Window* GetWindow()     { return mWindowPtr; }
    static bool IsQuitting()           { return mQuit; }

    static void SetScene(std::unique_ptr<Scene> aScene);

    static bool IsKeyPressed(const SDL_Scancode& aScancode);

    static double GetTime() { return mCurrentTime; }

  private:
    Environment() = default;

    static void ProcessSDLEvents();

    static std::unique_ptr<Environment> mInstancePtr;
    static std::unique_ptr<Scene> mScenePtr;

    // TODO: internal resolution?

    static SDL_Window* mWindowPtr;
    static SDL_GLContext mContext;
    static bool mQuit;
    static double mCurrentTime;
};

#endif
