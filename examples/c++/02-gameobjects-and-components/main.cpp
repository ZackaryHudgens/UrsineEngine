#include "Environment.hpp"

#include "PlayerObject.hpp"
#include "PlayerInputComponent.hpp"

int main()
{
  /**
   * Create a Scene and a PlayerObject, then add the PlayerObject to the Scene.
   */
  core::Scene testScene;
  auto player = std::make_unique<example_two::PlayerObject>();
  testScene.AddObject(std::move(player));

  /**
   * Create a window, load the Scene, and run the game. The PlayerInputComponent
   * contained in the PlayerObject will respond to key presses by printing
   * which key you pressed.
   */
  env.CreateWindow("Example 02 - GameObjects and Components", 800, 600);
  env.LoadScene(testScene);
  env.Run();

  return 0;
}
