#include "Environment.hpp"

#include <IL/ilu.h>
#include <iostream>

std::unique_ptr<Environment> Environment::mInstancePtr = nullptr;
std::unique_ptr<Scene> Environment::mScenePtr = nullptr;
SDL_Window*  Environment::mWindowPtr = nullptr;
bool Environment::mQuit = false;
double Environment::mCurrentTime = 0;

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
Environment* Environment::GetInstance()
{
  if(mInstancePtr == nullptr)
  {
    mInstancePtr.reset(new Environment());
  }

  return mInstancePtr.get();
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

void Environment::Update()
{
  // Before updating the current scene, poll the SDL event queue.
  ProcessSDLEvents();

  if(mScenePtr == nullptr)
  {
    mScenePtr.reset(new Scene());

    std::unique_ptr<GameObject> bkg = std::make_unique<GameObject>();
    std::unique_ptr<Animation> bkgA = std::make_unique<Animation>();
    std::unique_ptr<Texture> bkgT = std::make_unique<Texture>();

    bkgT->LoadFromFile("resources/bg.jpg");
    bkgA->SetTexture(std::move(bkgT));
    bkgA->AddFrame(SDL_Rect{0, 0, 1920, 1080});
    bkg->AddAnimation("default", std::move(bkgA));
    bkg->SetAnimation("default");

    mScenePtr->AddObject("bkg", std::move(bkg));

    std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
    std::unique_ptr<Animation> ani = std::make_unique<Animation>();
    std::unique_ptr<Texture> tex = std::make_unique<Texture>();

    tex->LoadFromFile("resources/test.jpg");
    ani->SetTexture(std::move(tex));
    ani->AddFrame(SDL_Rect{0, 0, 100, 100});
    ani->AddFrame(SDL_Rect{100, 100, 100, 100});
    ani->SetSpeed(0.1);
    obj->AddAnimation("default", std::move(ani));
    obj->SetAnimation("default");

    mScenePtr->AddObject("obj", std::move(obj));
  }
  else
  {
    mScenePtr->UpdateObjects();
  }

  // Update the current time in seconds.
  mCurrentTime = (double(SDL_GetTicks()) / double(1000));
}

void Environment::RenderScene()
{
  if(mScenePtr != nullptr)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    mScenePtr->RenderObjects();
  }

  SDL_GL_SwapWindow(mWindowPtr);
}

void Environment::SetScene(std::unique_ptr<Scene> aScene)
{
  mScenePtr = std::move(aScene);
}

// Polls the SDL event queue and decides what to do with the event.
void Environment::ProcessSDLEvents()
{
  SDL_Event e;

  if(SDL_PollEvent(&e) != 0)
  {
    switch(e.type)
    {
      case SDL_QUIT:
      {
        mQuit = true;
        break;
      }

      // TODO: Temporary
      case SDL_KEYDOWN:
      {
        switch(e.key.keysym.sym)
        {
          case SDLK_ESCAPE:
          {
            mQuit = true;
            break;
          }
          default:
          {
            break;
          }
        }
        break;
      }
      default:
      {
        if(mScenePtr != nullptr)
        {
          mScenePtr->ProcessSDLEvent(e);
        }
        break;
      }
    }
  }
}

// Returns true if the key corresponding to the given scancode is pressed.
bool Environment::IsKeyPressed(const SDL_Scancode& aScancode)
{
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    return keyboardState[aScancode];
}
