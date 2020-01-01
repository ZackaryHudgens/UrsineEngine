#include "Environment.hpp"

int main(int argc, char* args[])
{
  // Initialize the environment and begin the game loop.
  // Continue looping until the user has quit.
  if(gCore::env.Initialize("game!", 480, 270))
  {
    while(!gCore::env.IsQuitting())
    {
      gCore::env.Update();       // Updates each object in the scene.
      gCore::env.RenderScene();  // Renders each object in the scene.
    }
  }

  gCore::env.DeleteInstance();
  return 0;
}

