#include "Environment.hpp"

#include <IL/ilu.h>
#include <iostream>

using gCore::Environment;

// Initialize the environment instance to nullptr.
std::unique_ptr<Environment> Environment::mInstancePtr = nullptr;

/**
 * Environment constructor.
 */
Environment::Environment()
  : mScenePtr(nullptr)
  , mWindowPtr(nullptr)
  , mIsQuitting(false)
  , mUpdateInterval(0.0015)
  , mMaxUpdatesPerFrame(1000)
{
}

/**
 * Frees the SDL_Window and sets it to nullptr.
 */
Environment::~Environment()
{
  SDL_DestroyWindow(mWindowPtr);
  mWindowPtr = nullptr;
}

/** 
 * Returns the single environment instance, or creates one
 * if there isn't one already.
 */
Environment& Environment::GetInstance()
{
  if(mInstancePtr == nullptr)
  {
    mInstancePtr.reset(new Environment());
  }

  return *(mInstancePtr.get());
}

/**
 * Destroys the current environment instance.
 */
void Environment::DeleteInstance()
{
  if(mInstancePtr != nullptr)
  {
    mInstancePtr.reset(nullptr);
  }
}

/** 
 * Initializes the environment by:
 *  - initializing SDL
 *  - creating and displaying a window
 *  - creating an OpenGL context
 *  - initializng the OpenGL matrices
 *
 *  @param aTitle The title of the game window.
 *  @param aWidth The initial width of the game window.
 *  @param aHeight The initial height of the game window.
 */
bool Environment::Initialize(const char* aTitle, int aWidth, int aHeight)
{
  // Initialize SDL.
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::cout << "SDL encountered an error! " << SDL_GetError() << std::endl;
    return false;
  }

  // Set the version of OpenGL to 2.1.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  // Create the window.
  mWindowPtr = SDL_CreateWindow(aTitle,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                aWidth,
                                aHeight,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if(mWindowPtr == nullptr)
  {
    std::cout << "SDL couldn't create a window! " << SDL_GetError() << std::endl;
    return false;
  }

  // Create an OpenGL context.
  if(SDL_GL_CreateContext(mWindowPtr) == NULL)
  {
    std::cout << "SDL couldn't create an OpenGL context! " << SDL_GetError() << std::endl;
    return false;
  }

  // TODO: this sets up VSync. I might not want this in the future.
  if(SDL_GL_SetSwapInterval(1) < 0)
  {
    std::cout << "Couldn't set up VSync! " << SDL_GetError() << std::endl;
    return false;
  }

  // Initialize the projection matrix.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0.0, aWidth, aHeight, 0.0, 1.0, -1.0);

  // Initialize the modelview matrix.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Initialize clear color.
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Enable texturing.
  glEnable(GL_TEXTURE_2D);

  // Enable transparency.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Check for OpenGL errors.
  GLenum error = glGetError();
  if(error != GL_NO_ERROR)
  {
    std::cout << "Error intializing OpenGL! " << gluErrorString(error) << std::endl;
    return false;
  }

  // Initialize DevIL.
  ilInit();
  ilClearColour(255, 255, 255, 0);

  // Check for DevIL error.
  ILenum ilError = ilGetError();
  if(ilError != IL_NO_ERROR)
  {
    std::cout << "Error initializing DevIL! " << iluErrorString(ilError) << std::endl;
    return false;
  }

  return true;
}

/**
 * Begins the game loop and continues until the user quits.
 * Updates happen on a fixed timestep (15 ms by default),
 * while rendering is tied to the display's refresh rate
 * (see SDL_GL_SetSwapInterval in Initialize()).
 */
int Environment::Run()
{
  double previousTime = GetTime();
  double updateLag = 0.0;

  while(!mIsQuitting)
  {
    ProcessSDLEvents();

    // Add the amount of real time that has passed to the updateLag,
    // then avoid rendering until the game has caught up to real time.
    double elapsedTime = GetTime() - previousTime;
    previousTime = GetTime();
    updateLag += elapsedTime;

    int updateCounter = 0;
    while(updateLag >= mUpdateInterval)
    {
      Update();
      updateLag -= mUpdateInterval;

      // If we've hit a maximum number of updates (maybe because we're
      // running too slowly), break out of the loop instead of locking up.
      ++updateCounter;
      if(updateCounter >= mMaxUpdatesPerFrame)
      {
        std::cout << "Maximum number of updates reached!" << std::endl;
        break;
      }
    }

    Render();
  }

  return 0;
}

/**
 * Polls the SDL event queue and decides what to do with the event.
 */
void Environment::ProcessSDLEvents()
{
  SDL_Event e;

  if(SDL_PollEvent(&e) != 0)
  {
    switch(e.type)
    {
      case SDL_QUIT:
      {
        mIsQuitting = true;
        break;
      }
      default:
      {
        if(mScenePtr != nullptr)
        {
          mScenePtr->ProcessEvent(e);
        }
        break;
      }
    }
  }
}

/**
 * Updates the current Scene and all of the GameObjects therein.
 */
void Environment::Update()
{
  if(mScenePtr == nullptr)
  {
  }
  else
  {
    mScenePtr->Update();
  }
}

/**
 * Renders all of the GameObjects within the current Scene.
 */
void Environment::Render()
{
  if(mScenePtr != nullptr)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    mScenePtr->Render();
  }

  SDL_GL_SwapWindow(mWindowPtr);
}

/**
 * Sets the current Scene.
 *
 * @param aScene A unique_ptr to a Scene object, which the
 *               Environment takes ownership of.
 */
void Environment::SetScene(std::unique_ptr<Scene> aScene)
{
  mScenePtr = std::move(aScene);
}

/**
 * Sets the internal resolution, which is the resolution the game is
 * expected to run at before scaling to screen size.
 *
 * @param aWidth The internal width of the game window.
 * @param aHeight The internal height of the game window.
 */
void Environment::SetInternalResolution(int aWidth, int aHeight)
{
  mInternalWidth = aWidth;
  mInternalHeight = aHeight;
}

/** 
 * Returns true if the key corresponding to the given scancode is pressed.
 *
 * @param aScancode An SDL Scancode representing a key.
 */
bool Environment::IsKeyPressed(const SDL_Scancode& aScancode)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[aScancode];
}

/**
 * Returns the amount of time passed since SDL initialized (in seconds).
 */
double Environment::GetTime()
{
  return (double)(SDL_GetTicks()) / 1000.0;
}
