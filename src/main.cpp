#include "Environment.hpp"

int main(int argc, char* args[])
{
  // Initialize the environment and begin the game loop.
  // Continue looping until the user has quit.
  if(env->Initialize("game!", 480, 270))
  {
    while(!env->IsQuitting())
    {
      env->Update();       // Updates each object in the scene.
      env->RenderScene();  // Renders each object in the scene.
    }
  }

  env->DeleteInstance();
  return 0;
}

